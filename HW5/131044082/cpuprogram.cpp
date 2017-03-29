/*				AHMET MUZAFFER DÜLGER
					  13104082
			 SON GÜNCELLEME: 16.11.2016
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

void CPUProgram::ReadFile(string fileName)
{
	fstream inputFile;
	string line;

	inputFile.open(fileName);

	if(inputFile.fail())
	{
		cerr << "Cannot open file!!" << endl;
		exit(1);
	}

	while(!inputFile.eof())
	{	
		getline(inputFile, line);
		if(line != "")
		{
			text.push_back(line);
			numOfRow++;
		}
	}
}

string CPUProgram::getLine(int lineNumber)
{
	return (text[lineNumber]);
}

int CPUProgram::size()
{
	return numOfRow;
}

string CPUProgram::operator [] (const int index)
{
	if (index >= text.size() || index < 0)
	{
		cerr << "Faulty index number ([] operator)!!";
		return "";
	}
	else
		return (text[index]);
}

bool CPUProgram::operator == (const CPUProgram& myText)
{
	return (text.size() == myText.text.size());
}
bool CPUProgram::operator != (const CPUProgram& myText)
{
	return (text.size() != myText.text.size());
}
bool CPUProgram::operator < (const CPUProgram& myText)
{
	return (text.size() < myText.text.size());
}
bool CPUProgram::operator > (const CPUProgram& myText)
{
	return (text.size() > myText.text.size());
}
bool CPUProgram::operator <= (const CPUProgram& myText)
{
	return (text.size() <= myText.text.size());
}
bool CPUProgram::operator >= (const CPUProgram& myText)
{
	return (text.size() >= myText.text.size());
}

ostream& operator << (ostream& outputStream, const CPUProgram& myText)
{
	for (int i = 0; i < myText.text.size(); ++i)
	{	
		outputStream << myText.text[i] << endl;
	}

	return outputStream;
}

CPUProgram CPUProgram::operator () (const int start, const int finish)
{
	if(start >= finish || start < 0)
		cerr << "Faulty values (() operator)!!" << endl;
	else
	{
		CPUProgram temp;
		for (int i = start; i <= finish; ++i)
		{
			temp.text.push_back(text[i]);
			temp.numOfRow++;
		}

		return temp;
	}
}

void CPUProgram::operator += (string line)
{
	if(line == "")
		cerr << "Faulty string (+= operator)!! " << endl;
	else
	{
		text.push_back(line);
		numOfRow++;
	}
}

CPUProgram CPUProgram::operator --()
{
	text.pop_back();
	numOfRow--;
	return *this;
}

CPUProgram CPUProgram::operator --(int)
{
	CPUProgram temp;
	temp.text = text;
	temp.option = option;
	temp.numOfRow = numOfRow;

	text.pop_back();
	numOfRow--;
	return temp;
}

CPUProgram CPUProgram::operator +(const string line)const
{
	if(line != "")
	{
		CPUProgram temp;
		temp.text = text;
		temp.option = option;
		temp.numOfRow = numOfRow;

		temp.text.push_back(line);
		temp.numOfRow++;
		return temp;
	}
	else
	{
		cerr << "Faulty string parameter (+ operator)!!" << endl;
		exit(1);
	}
}

CPUProgram& CPUProgram::operator +(const CPUProgram& myText)
{
	for (int i = 0; i < myText.text.size(); ++i)
	{
		text.push_back(myText.text[i]);
		numOfRow++;
	}

	return *this;
}