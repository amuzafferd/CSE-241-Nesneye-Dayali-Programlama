/*				AHMET MUZAFFER DÜLGER
					  13104082
			 SON GÜNCELLEME: 08.11.2016
*/

#include "requiredIncs.h"

Computer::Computer(CPU myCPU, CPUProgram myCPUProgram, Memory myMemory, int opt)
{
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
	CPU cpu = getCPU();
	Memory myMem = getMem();

	while(!cpu.halted())
	{
		string instruction = getCPUProgram().getLine(cpu.getProgCounter()-1);
		cpu.execute(instruction, myMem);
	}
}