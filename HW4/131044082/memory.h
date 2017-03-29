/*				AHMET MUZAFFER DÜLGER
					  13104082
			 SON GÜNCELLEME: 08.11.2016
*/

#ifndef _MEMORY_H__
#define _MEMORY_H_

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>

using namespace std;

class Memory
{
	public:
		//Constructors
		Memory(int option);
		Memory();
		//Getters
		int getMemory(int index)const;
		int getOption()const;
		//Setters
		void setMemory(int index, int value);
		void setOption(int opt);
		//Memory arrayinin içindeki bütün elemanları ekrana basar.
		void printAll()const;
	private:
		uint8_t memory[50];
		int option;
};

#endif