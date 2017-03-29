/*				AHMET MUZAFFER DÜLGER
					  13104082
			 SON GÜNCELLEME: 08.11.2016
*/

#ifndef _COMPUTER_H__
#define _COMPUTER_H_

#include "cpu.h"
#include "cpuprogram.h"

using namespace std;
using namespace ahmetmuzaffer;

class Computer
{
	public:
		//Constructors
		Computer(const CPU& myCPU, const CPUProgram& myCPUProgram, const Memory& myMemory, int opt);
		Computer(const CPU& myCPU, const CPUProgramDyn& myCPUProgramDyn, const Memory& myMemory, int opt);
		Computer(int option);
		Computer();
		//Getters
		CPU getCPU()const;
		CPUProgram getCPUProgram()const;
		CPUProgramDyn getCPUProgramDyn()const;
		Memory getMem()const;
		int getOption()const;
		//Setters
		void setCPU(CPU newCPU);
		void setCPUProgram(CPUProgram newCPUProgram);		
		void setCPUProgramDyn(CPUProgramDyn newCPUProgramDyn);
		void setMem(Memory newMemory);
		void setOption(int opt);

		void execute();
	private:
		CPU myCpu;
		CPUProgram myCpuProgram;
		CPUProgramDyn myCPUProgramDyn;
		Memory myMem;
		int option;
		int state=0;
};

#endif