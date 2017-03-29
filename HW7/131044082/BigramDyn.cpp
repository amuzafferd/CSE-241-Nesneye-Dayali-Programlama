/*				AHMET MUZAFFER DÜLGER
					  131044082
			DATE LAST MODIFIED: 29.12.2016
*/

#include "BigramDyn.h"

using namespace std;

template<class T>
BigramDyn<T>::BigramDyn(int dType) throw(exception)
{
	dataType = dType;
	if(dataType != 1 && dataType != 2 && dataType != 3)
		throw invalid_argument("Invalid data type!!!");

	setCapacity(100);
	setUsed(0);
	allOfValuesInFileDyn = new T[capacity]; 
}

template<class T>
BigramDyn<T>::BigramDyn(const BigramDyn& objectDyn) throw(exception)
{
	setCapacity(objectDyn.getCapacity());
	setUsed(objectDyn.getUsed());
	dataType = objectDyn.dataType;
	if(dataType != 1 && dataType != 2 && dataType != 3)
		throw invalid_argument("Invalid data type!!!");

	allOfValuesInFileDyn = new T[capacity];

	for (int i = 0; i < objectDyn.getUsed(); ++i)
		allOfValuesInFileDyn[i] = objectDyn.allOfValuesInFileDyn[i];
}

template<class T>
BigramDyn<T>::~BigramDyn()
{
	delete [] allOfValuesInFileDyn;
	allOfValuesInFileDyn = nullptr;
}

template<class T>
int BigramDyn<T>::getUsed()const
{
	return used;
}

template<class T>
int BigramDyn<T>::getCapacity()const
{
	return capacity;
}

template<class T>
void BigramDyn<T>::setUsed(const int otherUsed)
{
	used = otherUsed;
}

template<class T>
void BigramDyn<T>::setCapacity(const int otherCapacity)
{
	capacity = otherCapacity;
}

template<class T>
void BigramDyn<T>::readFile(const string& fileName) throw(exception)
{
	fstream inputFile;

	inputFile.open(fileName);

	if (inputFile.fail())
		throw invalid_argument("Cannot open file!!");
	else
	{	inputFile >> value;
		if (inputFile.eof())
        	throw invalid_argument("This file is empty!!!");
       	else if(inputFile.fail())
	 		throw invalid_argument("Invalid argument!!!");
		else
		{
			inputFile.close();
			inputFile.open(fileName);
			while(!inputFile.eof())
			{
				inputFile >> value;
				if(inputFile.fail())
	 				throw invalid_argument("Invalid argument!!!");
				if(getUsed() > getCapacity())
					controlOfCapacity();
				allOfValuesInFileDyn[getUsed()] = value;
				setUsed(getUsed()+1);
			}
		}
	}
}

template<class T>
int BigramDyn<T>::numGrams()const
{
	return (getUsed() - 1);
}

template<class T>
int BigramDyn<T>::numOfGrams(T anyType1, T anyType2)const
{
	int count = 0;
	for (int i = 0; i < getUsed(); ++i)
	{
		if(allOfValuesInFileDyn[i] == anyType1 && allOfValuesInFileDyn[i+1] == anyType2)
			count++;
	}
	return count;
}

template<class T>
pair<T,T> BigramDyn<T>::maxGrams()const
{
	int count=0, tempInMaxGramDyn=0;
	pair<T,T> returnValue[getUsed() - 1];

	for(int i=0; i<getUsed(); i++)
	{
		for(int j=0; j<getUsed(); j++)
		{
			if(allOfValuesInFileDyn[i] == allOfValuesInFileDyn[j] && 
				allOfValuesInFileDyn[i+1] == allOfValuesInFileDyn[j+1])
					tempInMaxGramDyn++;
			if(tempInMaxGramDyn > count)
			{
				count = tempInMaxGramDyn;
				returnValue[1] = make_pair(allOfValuesInFileDyn[i], allOfValuesInFileDyn[i+1]);				
			}
		}
		tempInMaxGramDyn = 0;
	}

	return (make_pair(returnValue[1].first, returnValue[1].second));
}

template<class T>
void BigramDyn<T>::printMyObject(ostream& outputStream)
{
	pair<T,T> tempPair[getUsed()];
	int intArray[getUsed()-1];

	for (int i = 0; i < getUsed(); ++i)
		intArray[i] = 0;

	int i=0, j=1;
	for (; i < getUsed(), j < getUsed(); i++, j++)
	{
		tempPair[i] = make_pair(allOfValuesInFileDyn[i], allOfValuesInFileDyn[j]);
	}

	for (int i = 0; i < getUsed(); ++i)
	{
		int numberOfGram;
		numberOfGram = numOfGrams(tempPair[i].first, tempPair[i].second);
		intArray[i] = numberOfGram;
	}

	int temp;
	for (int i = 0; i < getUsed(); ++i)
	{
		for (int k = 0; k < getUsed(); ++k)
		{
			if(intArray[i] > intArray[k])
			{
				temp = intArray[k];
				intArray[k] = intArray[i];
				intArray[i] = temp;
			}
		}
	}

	outputStream << "------------------" << endl;
	outputStream << "operator << " << endl << endl;
	for (int i = 0; i < getUsed(); i++)
	{
		for (int k = 0; k < getUsed(); k++)
		{
			if((numOfGrams(allOfValuesInFileDyn[k], allOfValuesInFileDyn[k+1]) == intArray[i]) && (intArray[i] != intArray[i+1]) && (k < getUsed()-1))
				outputStream << "[" << allOfValuesInFileDyn[k] << " - " << allOfValuesInFileDyn[k+1] << "]" << 
								" -----> " << numOfGrams(allOfValuesInFileDyn[k], allOfValuesInFileDyn[k+1]) << endl;
		}
	}
	outputStream << "------------------";
}

template<class T>
void BigramDyn<T>::controlOfCapacity()
{
	T *temp;
	temp = new T[getCapacity()];
	for (int i = 0; i < getCapacity(); ++i)
		temp[i] = allOfValuesInFileDyn[i];

	delete [] allOfValuesInFileDyn;
	capacity += capacity;
	allOfValuesInFileDyn = new T[getCapacity()];

	for (int i = 0; i < getUsed(); ++i)
		allOfValuesInFileDyn[i] = temp[i];

	delete [] temp;
}