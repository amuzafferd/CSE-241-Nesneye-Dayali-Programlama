/*				AHMET MUZAFFER DÜLGER
					  131044082
			DATE LAST MODIFIED: 29.12.2016
*/

#ifndef _BIGRAM_H_
#define _BIGRAM_H_

#include <iostream>
#include <string>
#include <exception>

using namespace std;

template <class T>
class Bigram
{
	public:
		/*gönderilen filename den verileri okuyup oluşabilecek bütün bigramları hesaplar*/
		virtual void readFile(const string& fileName)=0;
		/*bütün bigramların sayısını return eder*/
		virtual int numGrams()const=0;
		/*parametre olarak aldığı bigram ikilisinden kaç tane olduğunu return eder*/
		virtual int numOfGrams(T anyType1, T anyType2)const=0;		
		/*dosyada en çok hangi bigram ikilisinin olduğunu return eder*/
		virtual pair<T,T> maxGrams()const=0;

		//http://stackoverflow.com/questions/4571611/making-operator-virtual
		//sitesi referans alınmıştır.(operator << ve printMyObject fonsiyonları)
		friend ostream& operator << (ostream& outputS, Bigram<T>& myBigram)
		{
			myBigram.printMyObject(outputS);
			return outputS;
		}
	protected:
		virtual void printMyObject(ostream& outputStream)=0;
};

#endif
