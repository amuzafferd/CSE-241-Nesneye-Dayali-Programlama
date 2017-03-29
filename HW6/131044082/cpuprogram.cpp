/*				AHMET MUZAFFER DÜLGER
					  13104082
			 SON GÜNCELLEME: 16.11.2016
*/

#include "cpuprogram.h"

using namespace std;

CPUProgram::CPUProgram(const int opt)
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


/****************************************************/
/***************DYNAMIC ARRAY CLASS******************/
/****************************************************/


namespace ahmetmuzaffer
{
	CPUProgramDyn::CPUProgramDyn(const int opt)
	{
		if(opt != 0 && opt != 1 && opt != 2)
		{
			cerr << "Wrong option !!" << endl;
			exit(1);
		}
		capacity = 10;
		used = 0;
		textDyn = new string[capacity];
		option = opt;
	}

	CPUProgramDyn::CPUProgramDyn()
	{
		capacity = 10;
		used = 0;
		textDyn = new string[capacity];
		option = 0;
	}

	CPUProgramDyn::CPUProgramDyn(const CPUProgramDyn& myDyn)
	{
		capacity = myDyn.capacity;
		used = myDyn.used;
		option = myDyn.option;
		numOfRow = myDyn.numOfRow;

		textDyn = new string[capacity];

		for (int i = 0; i < myDyn.used; ++i)
			textDyn[i] = myDyn.textDyn[i];
	}

	CPUProgramDyn::~CPUProgramDyn()
	{
		delete [] textDyn;
		textDyn = nullptr; //Cannot dangling pointer
	}

	string CPUProgramDyn::getLine(const int lineNumber)const
	{
		return (textDyn[lineNumber]);
	}

	int CPUProgramDyn::size()const
	{
		return used;
	}

	void CPUProgramDyn::ReadFile(string fileName)
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
			if(line != "" && line != "\n")
			{
				if(used >= capacity)
					controlOfCapacity();
				textDyn[used] = line;
				used++;
			}
		}
	}

	string CPUProgramDyn::operator [] (const int index)
	{
		if (index >= size() || index < 0)
		{
			cerr << "Faulty index number ([] operator)!!";
			return "";
		}
		else
			return (textDyn[index]);
	}

	bool CPUProgramDyn::operator == (const CPUProgramDyn& myText)
	{
		return (size() == myText.size());
	}
	bool CPUProgramDyn::operator != (const CPUProgramDyn& myText)
	{
		return (size() != myText.size());
	}
	bool CPUProgramDyn::operator < (const CPUProgramDyn& myText)
	{
		return (size() < myText.size());
	}
	bool CPUProgramDyn::operator > (const CPUProgramDyn& myText)
	{
		return (size() > myText.size());
	}
	bool CPUProgramDyn::operator <= (const CPUProgramDyn& myText)
	{
		return (size() <= myText.size());
	}
	bool CPUProgramDyn::operator >= (const CPUProgramDyn& myText)
	{
		return (size() >= myText.size());
	}

	ostream& operator << (ostream& outputStream, const CPUProgramDyn& myText)
	{
		for (int i = 0; i < myText.size(); ++i)
			outputStream << myText.textDyn[i] << endl;
		return outputStream;
	}

	CPUProgramDyn CPUProgramDyn::operator () (const int start, const int finish)
	{
		if(start >= finish || start < 0)
			cerr << "Faulty values (() operator)!!" << endl;
		else
		{
			CPUProgramDyn temp;

			temp.capacity = start + finish;

			delete [] temp.textDyn;

			temp.textDyn = new string[temp.capacity];

			for (int i = start; i <= finish; ++i)
			{
				temp.textDyn[temp.used] = textDyn[i];
				temp.used++;
			}
			return temp;
		}
	}

	void CPUProgramDyn::operator += (string line)
	{
		if(line == "")
			cerr << "Faulty string (+= operator)!! " << endl;
		else
		{
			if(used >= capacity)
				controlOfCapacity();
			
			textDyn[used] = line;
			used++;
		}
	}

	CPUProgramDyn CPUProgramDyn::operator --()
	{
		textDyn[used] = "";
		used--;
		return *this;
	}

	CPUProgramDyn CPUProgramDyn::operator --(int)
	{
		CPUProgramDyn temp;

		delete [] temp.textDyn;

		temp.option = option;
		temp.used = used;
		temp.capacity = capacity;

		temp.textDyn = new string[temp.capacity];

		for (int i = 0; i < temp.used; ++i)
			temp.textDyn[i] = getLine(i);


		textDyn[used] = "";
		used--;
		return temp;
	}

	CPUProgramDyn CPUProgramDyn::operator +(const string line)const
	{
		if(line != "")
		{
			CPUProgramDyn temp;

			delete [] temp.textDyn;
			temp.capacity = capacity;
			temp.used = used;

			temp.textDyn = new string[temp.capacity];

			if(temp.used >= temp.capacity)
				temp.controlOfCapacity();

			temp.textDyn[temp.used] = line;
			temp.used++;
			return temp;
		}
		else
		{
			cerr << "Faulty string parameter (+ operator)!!" << endl;
			exit(1);
		}
	}

	const CPUProgramDyn& CPUProgramDyn::operator +(const CPUProgramDyn& myText)
	{
		string temp[used];

		for (int i = 0; i < used; ++i)
		{
			temp[i] = textDyn[i];
		}


		delete [] textDyn;

		capacity = used + myText.used;

		textDyn = new string[capacity];

		for (int i = 0; i < used; ++i)
			textDyn[i] = temp[i];

		for (int i = 0; i < myText.used; ++i)
			textDyn[used++] = myText.textDyn[i];

		return *this;
	}

	void CPUProgramDyn::controlOfCapacity()
	{
		string *temp;
		temp = new string[capacity];
		for (int i = 0; i < capacity; ++i)
			temp[i] = getLine(i);
		
		delete [] textDyn;
		capacity += capacity;
		textDyn = new string[capacity];

		for (int i = 0; i < used; ++i)
			textDyn[i] = temp[i];

		delete [] temp;
	}
}