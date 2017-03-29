/*				AHMET MUZAFFER DÜLGER
					  131044082
			DATE LAST MODIFIED: 29.12.2016
*/

#ifndef _BIGRAMDYN_H_
#define _BIGRAMDYN_H_

#include "Bigram.h"
#include <iostream>
#include <string>
#include <exception>
#include <fstream>

using namespace std;

template <class T>
class BigramDyn: public Bigram<T>
{
	public:
		//constructors
		BigramDyn(int dType) throw(exception);
		BigramDyn(const BigramDyn& objectDyn) throw(exception);		
		//destructors
		~BigramDyn();
		//getters
		int getUsed()const;
		int getCapacity()const;
		//setters
		void setUsed(const int otherUsed);
		void setCapacity(const int otherCapacity);
		//gönderilen filename den verileri okuyup oluşabilecek bütün bigramları hesaplar
		void readFile(const string& fileName) throw(exception);
		//bütün bigramların sayısını return eder
		int numGrams()const;
		//parametre olarak aldığı bigram ikilisinden kaç tane olduğunu return eder
		int numOfGrams(T anyType1, T anyType2)const;
		//dosyada en çok hangi bigram ikilisinin olduğunu return eder
		pair<T,T> maxGrams()const;
		//eğer capacity dolduysa yeni capacity ile aldığı yeri büyütür
		void controlOfCapacity();
	protected:
		virtual void printMyObject(ostream& outputStream); 
	private:
		T* allOfValuesInFileDyn;
		int dataType;
		int capacity;
		int used;
		T value;
};

#endif