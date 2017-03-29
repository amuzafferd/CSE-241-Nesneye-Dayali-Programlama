/*				AHMET MUZAFFER DÜLGER
					  13104082
			 SON GÜNCELLEME: 16.11.2016
*/

#include "memory.h"

Memory::Memory(int option)
{
	if(option != 0 && option != 1 && option != 2)
	{
		cerr << "Wrong option !!" << endl;
		exit(1);
	}
	setOption(option);
	for (int i=0; i<50; ++i)
	{
		setMemory(i,(uint8_t)0);
	}
}

Memory::Memory()
{
	setOption(0);
	for (int i=0; i<50; ++i)
	{
		setMemory(i,(uint8_t)0);
	}
}

int Memory::getMemory(int index)const
{
	return memory[index];
}

void Memory::setMemory(int index, int value)
{
	memory[index] = value;
}

int Memory::getOption()const
{
	return option;
}

void Memory::setOption(int opt)
{
	option = opt;
}

void Memory::printAll()const
{
	for (int i=0; i<50; ++i)
		cout << "[" << i << "] -> " << (unsigned)getMemory(i) << endl;
}