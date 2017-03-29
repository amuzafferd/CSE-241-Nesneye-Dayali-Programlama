#ifndef _CPU_H__
#define _CPU_H_

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <limits>
#include <string>

using namespace std;

class CPU
{
	public:
		CPU(int fileSize=0,int value=0, int firstProgCounter=1, string opt="0");
		void setRegister(int index, int value);
		void setProgCounter(int firstProgCounter);
		int getRegister(int index)const;
		int getProgCounter()const;
		void execute(string text);
		void print()const;
		bool halted()const;
	private:
		int registers[5];
		static int progCounter;
		int size;
		string option;
		void mov(string R1, string R2);
		void add(string R1, string R2);
		void sub(string R1, string R2);
		int stringToInt(string str);
		int controlOfR(string R1);
		string stringUpper(string text);
		void instructionControl(string text, string& instruction, string& r1, string& r2);
		void jmp(string lineNumber);
		void printReg(string R);
};

#endif
