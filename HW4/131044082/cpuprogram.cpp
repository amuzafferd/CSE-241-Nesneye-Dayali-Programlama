/*				AHMET MUZAFFER DÜLGER
					  13104082
			 SON GÜNCELLEME: 08.11.2016
*/

#include "cpuprogram.h"

using namespace std;

CPUProgram::CPUProgram(int opt)
{
	if(opt != 0 && opt != 1 && opt != 2)
	{
		cerr << "Wrong option !!" << endl;
		exit(1);
	}
	option = opt;
}

CPUProgram::CPUProgram()
{
	option = 0;
}

void CPUProgram::readFile(string fileName)
{
	fstream inputFile;
	string line;

	inputFile.open(fileName);

	if(inputFile.fail())
	{
		cerr << "Cannot open file!!" << endl;
		exit(1);
	}

	int i=0;
	while(!inputFile.eof())
	{
		getline(inputFile, line);
		textFile[i] = line;
		i++;
	}
}

string CPUProgram::getLine(int lineNumber)
{
	return (textFile[lineNumber]);
}

int CPUProgram::size()
{
	int i=0;
	while(!textFile[i].empty())
		i++;
	return i;
}