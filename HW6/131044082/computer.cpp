/*				AHMET MUZAFFER DÜLGER
					  13104082
			 SON GÜNCELLEME: 16.11.2016
*/

#include "computer.h"

Computer::Computer(const CPU& myCPU, const CPUProgram& myCPUProgram,const Memory& myMemory, int opt)
{
	state = 0;
	if(option != 0 && option != 1 && option != 2)
	{
		cerr << "Wrong option !!" << endl;
		exit(1);
	}
	setCPU(myCPU);
	setCPUProgram(myCPUProgram);
	setMem(myMemory);
	setOption(opt);
}

Computer::Computer(const CPU& myCPU, const CPUProgramDyn& myCPUProgramDyn, const Memory& myMemory, int opt)
{
	state = 1;
	if(option != 0 && option != 1 && option != 2)
	{
		cerr << "Wrong option !!" << endl;
		exit(1);
	}
	setCPU(myCPU);
	setCPUProgramDyn(myCPUProgramDyn);
	setMem(myMemory);
	setOption(opt);
}

Computer::Computer(int option)
{
	if(option != 0 && option != 1 && option != 2)
	{
		cerr << "Wrong option !!" << endl;
		exit(1);
	}
	setOption(option);
}

Computer::Computer()
{
	setOption(0);
}

CPU Computer::getCPU()const
{
	return myCpu;
}

CPUProgram Computer::getCPUProgram()const
{
	return myCpuProgram;
}

CPUProgramDyn Computer::getCPUProgramDyn()const
{
	return myCPUProgramDyn;
}

Memory Computer::getMem()const
{
	return myMem;
}

int Computer::getOption()const
{
	return option;
}

void Computer::setCPU(CPU newCPU)
{
	myCpu = newCPU;
}

void Computer::setCPUProgram(CPUProgram newCPUProgram)
{
	myCpuProgram = newCPUProgram;
}

void Computer::setCPUProgramDyn(CPUProgramDyn newCPUProgramDyn)
{
	myCPUProgramDyn = newCPUProgramDyn;
}

void Computer::setMem(Memory newMemory)
{
	myMem = newMemory;
}

void Computer::setOption(int opt)
{
	option = opt;
}

void Computer::execute()
{
	Memory myMem = getMem();
	CPU cpu = getCPU();

	if(state == 0)
	{	
		while(!cpu.halted())
		{
			cout << "state= " << state << endl;
			string instruction = getCPUProgram().getLine(cpu.getProgCounter()-1);
			cpu.execute(instruction, myMem);
		}
	}
	else if(state == 1)
	{
		while(!cpu.halted())
		{
			cout << "state= " << state << endl;
			string instruction = getCPUProgramDyn().getLine(cpu.getProgCounter()-1);
			cpu.execute(instruction, myMem);
		}
	}
	else
	{
		cerr << "Wrong state!!" << endl;
		exit(1);
	}
}