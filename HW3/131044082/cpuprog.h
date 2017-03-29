#ifndef _CPUPROG_H__
#define _CPUPROG_H__

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <limits>

using namespace std;

class CPUProg
{
	public:
		CPUProg(string fileName);
		void readFile(string fileName);
		string getLine(int lineNumber);
		int size();
		
	private:
		string textFile[200];
};

#endif