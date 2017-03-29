import java.util.*;
import java.io.*;

public class BigramMap<E> implements Bigram<E>
{
	private int dataType;
	private Map<E,E> allOfValuesInFileMap;
	private Object temp;
	private Object value;
	private int numberOfGrams = 0;

	//constructors
	public BigramMap()
	{
		dataType = 2; // dataType hiç gelmez ise string ile çalışır.
	}

	public BigramMap(int dType)
	{
		dataType = dType;
	}
	
	//gönderilen filename den verileri okuyup oluşabilecek bütün bigramları hesaplar
	public void readFile(String fileName)
	{
		allOfValuesInFileMap = new HashMap<E,E>();

		File input = new File(fileName);
		Scanner inputFile = null;

		try
		{
			inputFile = new Scanner(input);
			while(inputFile.hasNextLine())
			{
				Scanner s2 = new Scanner(inputFile.nextLine());
				value = s2.next();
				while(s2.hasNext())
				{
					temp = s2.next();
					allOfValuesInFileMap.put((E)value, (E)temp);
					value = temp;
					numberOfGrams++;
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
		return numberOfGrams;
	}

	public int numOfGrams(E anyType1, E anyType2)
	{
		System.out.println("numOfGrams!! Sadece BigramDyn çalışıyor.");
		return 0;
	}

	public String toString()
	{
		System.out.println("toString!! Sadece BigramDyn çalışıyor.");
		return " ";
	}
}