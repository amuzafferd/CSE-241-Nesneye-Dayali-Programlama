/*				AHMET MUZAFFER DÜLGER
					  13104082
			 SON GÜNCELLEME: 08.11.2016
*/

#ifndef _COMPUTER_H__
#define _COMPUTER_H_

#include "cpu.h"
#include "cpuprogram.h"

using namespace std;

class Computer
{
	public:
		//Constructors
		Computer(CPU myCPU, CPUProgram myCPUProgram, Memory myMemory, int opt);
		Computer(int option);
		Computer();
		//Getters
		CPU getCPU()const;
		CPUProgram getCPUProgram()const;
		Memory getMem()const;
		int getOption()const;
		//Setters
		void setCPU(CPU newCPU);
		void setCPUProgram(CPUProgram newCPUProgram);
		void setMem(Memory newMemory);
		void setOption(int opt);

		void execute();
	private:
		CPU myCpu;
		CPUProgram myCpuProgram;
		Memory myMem;
		int option;
};

#endif