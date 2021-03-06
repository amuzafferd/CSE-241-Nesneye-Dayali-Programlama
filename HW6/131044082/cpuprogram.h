/*				AHMET MUZAFFER DÜLGER
					  13104082
			 SON GÜNCELLEME: 08.11.2016
*/

#ifndef _CPUPROGRAM_H__
#define _CPUPROGRAM_H__

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>

using namespace std;

class CPUProgram
{
	public:
		//Constructors
			CPUProgram(const int opt);
			CPUProgram();
		//Dosyayı açma işlemleri, okuma ve okuduğu satırı textFile a yazma işlemlerini yapar.
			void ReadFile(string fileName);
		//txt dosyası içerisindeki toplam satır sayısını return eder.
			int size();
		//textFile dan istenilen satırı return eder.
			string getLine(int lineNumber);		
		//index operator overload
			string operator [] (const int index);
		//compare operators overload
			bool operator == (const CPUProgram& myText);
			bool operator != (const CPUProgram& myText);
			bool operator < (const CPUProgram& myText);
			bool operator > (const CPUProgram& myText);
			bool operator <= (const CPUProgram& myText);
			bool operator >= (const CPUProgram& myText);
		//output stream operator overload
			friend ostream& operator << (ostream& outputStream, const CPUProgram& myText);
		//funtion call operator overload
			CPUProgram operator () (const int start, const int finish);
		//+= operator overload
			void operator += (string line);
		//post and pre decrement operators overload
			CPUProgram operator --();
			CPUProgram operator --(int);
		//+ operator overload
			CPUProgram operator +(const string line)const;
			CPUProgram& operator +(const CPUProgram& myText);
		
	private:
		vector<string> text;
		int option;
		int numOfRow=0;
};


namespace ahmetmuzaffer
{
	class CPUProgramDyn
	{
		public:
			//Constructors
				CPUProgramDyn(const int opt);
				CPUProgramDyn();
				CPUProgramDyn(const CPUProgramDyn& myDyn);
			//Destructor
				~CPUProgramDyn();
			//Dosyayı açma işlemleri, okuma ve okuduğu satırı textFile a yazma işlemlerini yapar.
				void ReadFile(string fileName);
			//txt dosyası içerisindeki toplam satır sayısını return eder.
				int size()const;
			//textFile dan istenilen satırı return eder.
				string getLine(const int lineNumber)const;		
			//index operator overload
				string operator [] (const int index);
			//compare operators overload
				bool operator == (const CPUProgramDyn& myText);
				bool operator != (const CPUProgramDyn& myText);
				bool operator < (const CPUProgramDyn& myText);
				bool operator > (const CPUProgramDyn& myText);
				bool operator <= (const CPUProgramDyn& myText);
				bool operator >= (const CPUProgramDyn& myText);
			//output stream operator overload
				friend ostream& operator << (ostream& outputStream, const CPUProgramDyn& myText);
			//funtion call operator overload
				CPUProgramDyn operator () (const int start, const int finish);
			//+= operator overload
				void operator += (string line);
			//post and pre decrement operators overload
				CPUProgramDyn operator --();
				CPUProgramDyn operator --(int);
			//+ operator overload
				CPUProgramDyn operator +(const string line)const;
				const CPUProgramDyn& operator +(const CPUProgramDyn& myText);

			void controlOfCapacity();
			
		private:
			string *textDyn;
			int option;
			int numOfRow=0;
			int capacity;
			int used;
	};
}

#endif