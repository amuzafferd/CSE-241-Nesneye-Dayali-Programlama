/*				AHMET MUZAFFER DÜLGER
					  131044082
			DATE LAST MODIFIED: 29.12.2016
*/

#ifndef _BIGRAMMAP_H_
#define _BIGRAMMAP_H_

#include "Bigram.h"
#include <fstream>
#include <map>

template <class T>
class BigramMap:public Bigram<T>
{
	public:
		//constructor
		BigramMap(int dType)throw(exception);
		//gönderilen filename den verileri okuyup oluşabilecek bütün bigramları hesaplar
		void readFile(const string& fileName) throw(exception);
		//bütün bigramların sayısını return eder
		int numGrams()const;
		//parametre olarak aldığı bigram ikilisinden kaç tane olduğunu return eder
		int numOfGrams(T anyType1, T anyType2)const;
		//dosyada en çok hangi bigram ikilisinin olduğunu return eder
		pair<T,T> maxGrams()const;	
	protected:	
		virtual void printMyObject(ostream& outputStream);
	private:
		multimap<T,T> allOfValuesInFileMap;
		T value;
		T temp;
		int dataType;
};

#endif