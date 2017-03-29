import java.util.*;
import java.io.*;
 

public class BigramDyn<E> implements Bigram<E>
{
	private int dataType;
	private E[] allOfValuesInFileDyn;
	private int capacity=0;
	private int used=0;
	private Object value;
	
	//constructors
	public BigramDyn()
	{
		dataType = 2; // dataType hiç gelmez ise string ile çalışır.
	}

	public BigramDyn(int dType) throws Exception
	{
		dataType = dType;
		if(dataType != 1 && dataType != 2 && dataType != 3)
   			throw new Exception("Invalid dataType !!! ");  
		else
		{
			setCapacity(5);
			setUsed(0);
			allOfValuesInFileDyn = (E[]) new Object[capacity];
		}
	}

	//setters
	public void setCapacity(int newCapacity)
	{
		this.capacity = newCapacity;
	}

	public void setUsed (int newUsed)
	{
		this.used = newUsed;
	}

	//getters
	public int getCapacity()
	{
		return capacity;
	}

	public int getUsed()
	{
		return used;
	}

	//gönderilen filename den verileri okuyup oluşabilecek bütün bigramları hesaplar
	public void readFile(String fileName)
	{
		File input = new File(fileName);
		Scanner inputFile = null;

		try
		{
			inputFile = new Scanner(input);
			while(inputFile.hasNextLine())
			{
				Scanner s2 = new Scanner(inputFile.nextLine());
				
				while(s2.hasNext())
				{
					value = s2.next();
					allOfValuesInFileDyn[getUsed()] = (E) value;
					setUsed( getUsed() + 1 );					
					if(getUsed() >= getCapacity())
						controlOfCapacity();
				}
			}
		}
		catch(Exception e)
		{
			System.err.println(e);
		}
	}
	
	//bütün bigramların sayısını return eder
	public int numGrams()
	{
		return( getUsed() - 1 );
	}

	//parametre olarak aldığı bigram ikilisinden kaç tane olduğunu return eder
	public int numOfGrams(E anyType1, E anyType2)
	{
		int count = 0;

		for (int i = 0; i < getUsed() - 1; ++i)
		{
			if((String.valueOf(allOfValuesInFileDyn[i])).equals((String.valueOf(anyType1)))	&& (String.valueOf(allOfValuesInFileDyn[i+1])).equals((String.valueOf(anyType2))))	
				count++;
		}

		return count;
	}

	//arrayin içini azalan sırayla ekrana basar
	public String toString()
	{
		int[] intArray = new int[getUsed()];

		for (int i=0; i < getUsed(); ++i)
			intArray[i] = 0;


		int numberOfGram;
		for (int i = 0, j=1; i < getUsed(); ++i, ++j)
		{
			numberOfGram = numOfGrams(allOfValuesInFileDyn[i], allOfValuesInFileDyn[j]);
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

		System.out.println("----------------------------");

		for (int i = 0; i < getUsed(); i++)
		{
			for (int k = 0; k < getUsed()-1; k++)
			{
				if((numOfGrams(allOfValuesInFileDyn[k], allOfValuesInFileDyn[k+1]) == intArray[i]) && 
					(intArray[i] != intArray[i+1]))
					System.out.println("[" + allOfValuesInFileDyn[k] + " - " + allOfValuesInFileDyn[k+1] + "]" + " -----> " + numOfGrams(allOfValuesInFileDyn[k], allOfValuesInFileDyn[k+1]));
			}
		}
		
		System.out.println("----------------------------");

		return " ";
	}

	//eğer capacity dolduysa yeni capacity ile aldığı yeri büyütür
	public void controlOfCapacity()
	{
		E[] temp;
		temp = (E[]) new Object[capacity];

		for(int i=0; i < getCapacity(); ++i)
			temp[i] = allOfValuesInFileDyn[i];

		capacity += capacity;

		allOfValuesInFileDyn = (E[]) new Object[getCapacity()];

		for (int i=0; i < getUsed(); i++) 
			allOfValuesInFileDyn[i] = temp[i];	
	}
}
