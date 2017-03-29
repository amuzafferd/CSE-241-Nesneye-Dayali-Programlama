#include "cpuprog.h"

using namespace std;

CPUProg::CPUProg(string fileName)
{
	readFile(fileName);
}

void CPUProg::readFile(string fileName)
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

string CPUProg::getLine(int lineNumber)
{
	return (textFile[lineNumber-1]);
}

int CPUProg::size()
{
	int i=0;
	while(!textFile[i].empty())
		i++;
	return i;
}