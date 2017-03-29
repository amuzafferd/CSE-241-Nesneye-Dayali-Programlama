/*				AHMET MUZAFFER DÜLGER
					  131044082
			DATE LAST MODIFIED: 29.12.2016
*/

#include "BigramMap.h"

template<class T>
BigramMap<T>::BigramMap(int dType) throw(exception)
{
	dataType = dType;
	if(dataType != 1 && dataType != 2 && dataType != 3)
		throw invalid_argument("Invalid data type!!!");
}

template <class T>
void BigramMap<T>::readFile(const string& fileName) throw(exception)
{
	fstream inputFile;
    inputFile.open( fileName ); 
    
    if(inputFile.fail())
    	throw invalid_argument("Cannot open file!!!");
    else
    {
        inputFile >> temp;        
	 	if(inputFile.eof())
        	throw invalid_argument("This file is empty!!!");
	 	else if(inputFile.fail())
	 		throw invalid_argument("Invalid argument!!!");
	    else
	    {
		    while(!inputFile.eof())
		    {
		    	inputFile >> value;
		        if(inputFile.fail())
	 				throw invalid_argument("Invalid argument!!!");
		        else
		        {	
			    	allOfValuesInFileMap.insert(pair<T,T> (temp, value));
			    	temp = value;
			    }
		    }
		}
	}

    inputFile.close();
}

template <class T>
int BigramMap<T>::numGrams()const
{
	return (allOfValuesInFileMap.size());
}

template <class T>
int BigramMap<T>::numOfGrams(T anyType1, T anyType2)const
{
	int count=0;
	for(auto iter = allOfValuesInFileMap.begin(); iter != allOfValuesInFileMap.end(); iter++)
	{
		if(iter->first == anyType1 && iter->second == anyType2)
			count++;
	}
	return count;
}

template<class T>
void BigramMap<T>::printMyObject(ostream& outputStream)
{
	int intArray[allOfValuesInFileMap.size()];

	for (int i = 0; i < allOfValuesInFileMap.size(); ++i)
		intArray[i] = 0;

	int j = 0;
	for (auto iter2 = allOfValuesInFileMap.begin(); iter2 != allOfValuesInFileMap.end(); iter2++)
	{
		int numberOfGram;
		numberOfGram = numOfGrams(iter2->first, iter2->second);
		intArray[j] = numberOfGram;
		j++;
	}

	int temp;
	for (int i = 0; i < allOfValuesInFileMap.size(); ++i)
	{
		for (int k = 0; k < allOfValuesInFileMap.size(); ++k)
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
	for (int i = 0; i < allOfValuesInFileMap.size(); ++i)
	{
		for (auto iter = allOfValuesInFileMap.begin(); iter != allOfValuesInFileMap.end(); iter++)
		{
			if((numOfGrams(iter->first, iter->second) == intArray[i]) && (intArray[i] != intArray[i+1]))
			{
				outputStream << "[" << iter->first << " - " << iter->second << "]" << " -----> " 
				<< numOfGrams(iter->first, iter->second) << endl; 
			}
		}
	}
	outputStream << "------------------";
}

template <class T>
pair<T,T> BigramMap<T>::maxGrams()const
{
	map<T,T> tempTemplate;
	int count=0, tempInMaxGramMap=0;

	auto it = allOfValuesInFileMap.begin();

	for(auto iter = allOfValuesInFileMap.begin(); iter != allOfValuesInFileMap.end(); iter++)
	{
		for (auto iter2 = allOfValuesInFileMap.begin(); iter2 != allOfValuesInFileMap.end(); iter2++)
		{
			if (iter->first == iter2->first && iter->second == iter2->second)
				tempInMaxGramMap++;
			if(tempInMaxGramMap > count)
			{
				count = tempInMaxGramMap;
				tempTemplate.insert(pair<T,T> (iter2->first, iter2->second));
				it = iter2;
			}
		}
		tempInMaxGramMap = 0;
	}

	return *it;
}