/*				AHMET MUZAFFER DÜLGER
					  13104082
			 SON GÜNCELLEME: 08.11.2016
*/

#ifndef _CPUPROGRAM_H__
#define _CPUPROGRAM_H__

#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

class CPUProgram
{
	public:
		//Constructors
		CPUProgram(int opt);
		CPUProgram();
		//Dosyayı açma işlemleri, okuma ve okuduğu satırı textFile a yazma işlemlerini yapar.
		void readFile(string fileName);
		//textFile dan istenilen satırı return eder.
		string getLine(int lineNumber);
		//txt dosyası içerisindeki toplam satır sayısını return eder.
		int size();
		
	private:
		string textFile[200];
		int option;
};

#endif