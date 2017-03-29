/*				AHMET MUZAFFER DÜLGER
					  13104082
			 SON GÜNCELLEME: 08.11.2016
*/

#ifndef _CPU_H__
#define _CPU_H_

#include "memory.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>

using namespace std;

class CPU
{
	public:
		//Constructors
		CPU(int opt);
		CPU();
		//Getters
		int getRegister(int index)const;
		int getProgCounter()const;
		int getSize()const;
		int getOption()const;
		//Setters
		void setRegister(int index, int value);
		void setProgCounter(int firstProgCounter);
		void setSize(int newSize);
		void setOption(int opt);

		void execute(string text, Memory& myMem);
		//registers arrayinin tamamını ekrana basar.
		void print()const;
		//Programın sonra bulma işlemi burada gerçekleşir.
		bool halted()const;
	private:
		int registers[5];
		static int progCounter;
		int size;
		int option;
		//MOV ile karşılaşıldığında registerlara veya memorye atama yapılır.
		void mov(string R1, string R2, Memory& myMem);
		//ADD ile karşılaşıldığında gönderilen registerların veya memorylerin değerlerini topla.
		void add(string R1, string R2, Memory& myMem);
		//SUB ile karşılaşıldığında gönderilen registerların veya memorylerin değerlerini çıkarır.
		void sub(string R1, string R2, Memory& myMem);
		//JMP ile karşışaışdığında istenilen satıra atlar.
		void jmp(string lineNumber);
		//JPN ile karşışaışdığında istenilen satıra atlar.
		void jpn(string lineNumber);
		//Gönderilen string i integer a çevirir.
		int stringToInt(string str);
		//Gönderilen registera göre hangi array kullanılacaksa onu return eder.
		int controlOfR(string R1);
		//Gönderilen text te geçen küçük harfleri büyük harflere çevirir.
		string stringUpper(string text);
		//Gönderilen stringten instruction ve registerların değerleri çeker.
		void instructionControl(string text, string& instruction, string& r1, string& r2);
		//İstenilen register ı veya memory yi ekrana basar.
		void printReg(string R, Memory& memory);
};

#endif