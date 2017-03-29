import java.util.*;
import java.io.*;

public interface Bigram<E>
{
	public void readFile(String fileName);
	public int numGrams();
	public int numOfGrams(E anyType1, E anyType2);
	public String toString();
}