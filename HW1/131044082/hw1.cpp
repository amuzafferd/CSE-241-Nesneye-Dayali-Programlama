/*				AHMET MUZAFFER DÜLGER
					  13104082
			DATE LAST MODIFIED: 09.10.2016
*/

#include <iostream>
#include <istream>
#include <fstream>
#include <cstdlib>

using namespace std;

void mov(int registerArray[], string R1, string R2);
void prn(int registerArray[], string ins, string R, string text, int argvValue);
void add(int registerArray[], string R1, string R2);
void sub(int registerArray[], string R1, string R2);
void hlt(int registerArray[]);
int stringToInt(string str);
int controlOfR(string R1);
string stringUpper(string text);
void isntructionControl(string text, string& instruction, string& r1, string& r2);

int main(int argc, char const *argv[])
{
    fstream inputFile;
    int registers[5] = {0};
    string text, instruction, r1, r2;	

	// Konsoldan girilen değerlerin sayısının 3 olması kontrolü
	if(argc != 3)
	{
		cerr << "Fault arguments !!" << endl;
		exit(1);
	}

	// Option kontrolü
	if(*argv[2] != '0' && *argv[2] != '1')
	{
		cerr << "Wrong option !!" << endl;
		exit(1);
	}
	
	inputFile.open(argv[1]);
	
	// Dosyanın açılıp açılmaması kontrolü
	if(inputFile.fail())
	{
		cerr << "File cannot open !!" << endl;
		exit(1);
	}	
	
	int argValue = 0;
	argValue = stringToInt(argv[2]);
	
	// Dosya sonu gelene kadar döngü çalışır
    while(!inputFile.eof())
    {
        getline(inputFile, text);
		
		isntructionControl(text,instruction,r1,r2); /*instruction, r1, r2
													  kontrolleri yapılıyor.*/
        if(instruction == "MOV")
        {					
			mov(registers, r1, r2);
			prn(registers,instruction,r1,text,argValue);       
        }
        else if(instruction == "ADD")
        {
			add(registers, r1, r2);
        	prn(registers,instruction,r1,text,argValue);
        }
        else if(instruction == "SUB")
        {
			sub(registers, r1, r2);
			prn(registers,instruction,r1,text,argValue);
        }
        else if(instruction == "PRN")
       	{
        	prn(registers,instruction,r1,text,argValue);
        }
        else if(instruction == "JMP")
        {
      		if(stringToInt(r2) != 0)	// JMP R1, 3 şeklindeki komutun
			{							// çalışması burada kontrol ediliyor.
				int temp=0,reg=0;
				reg = controlOfR(r1);
				temp = registers[reg];
				
				if(temp == 0)
				{
					inputFile.close();
					inputFile.open(argv[1]);
					for(int i=0; i<stringToInt(r2)-1;++i)
						getline(inputFile, text);					
				}
			}	
			else if(stringToInt(r2) == 0)	// JMP 2 şeklindeki komutun
			{								// kontrolü burada yapılıyor.
				inputFile.close();
				inputFile.open(argv[1]);
				for(int i=0; i<stringToInt(r1)-1;++i)
					getline(inputFile, text);
			}
			prn(registers,instruction,r1,text,argValue);

        }
        else if(instruction == "HLT")
        {
			hlt(registers);
			prn(registers,instruction,r1,text,argValue);	
			exit(1);
		}
		
        instruction.clear();
        r1.clear();
        r2.clear();
    }

    inputFile.close();
    return 0;

}
// Gönderilen stringten instruction ve registerların değerleri çeker.
void isntructionControl(string text, string& instruction, string& r1, string& r2)
{
	int i=0; int j=0;
		
    while(text[i] != '\0' && text[i] != ';')
    {
        if(text[i] != ' ' && text[i] != ',')
        {
            if(j<3)
                instruction += text[i];
            else if(j>=3 && j<5)
                r1 += text[i];
            else if(j>=5)
                r2 += text[i];
            i++;
            j++;
        }
        else
            i++;
    }
	instruction = stringUpper(instruction);
	r1 = stringUpper(r1);
	r2 = stringUpper(r2);
}

// Option değeri kontrol edildikten sonra PRN komutu ona göre çalışır.
void prn(int registerArray[], string ins, string R, string text, int argvValue)
{
	if(argvValue == 0 && ins == "PRN")
	{
		int reg=0;
		reg=controlOfR(R);
	
		if(R=="R1" || R=="R2" || R=="R3" || R=="R4" || R=="R5")
			cout << "R" << reg+1 << "=" << registerArray[reg] << endl;
		else
			cout << reg << endl;
	}
	else if(argvValue == 1)
	{
		for(int i=0; i<5; i++)
		cout << "R" << i+1 << "=" << registerArray[i] << "  " ;
		cout << endl;
		for(int i=0; text[i] != ';' && text[i] != '\0' ; i++)
			cout << text[i];
		cout << endl;
	}	
}
// HLT ile karşılaşıldığı zaman bütün registerların değeri ekrana basılır.
void hlt(int registerArray[])
{
    int i;
    for(i=0; i<5; i++)
		cout << "R" << i+1 << "=" << registerArray[i] << "  " ;
	cout << endl;	
}
// ADD ile karşılaşıldığın gönderilen registerların değerlerini topla.
void add(int registerArray[], string R1, string R2)
{
	int reg1=0,reg2=0;	
	
	reg1 = controlOfR(R1);
	reg2 = controlOfR(R2);
	
	if(R2=="R1" || R2=="R2" || R2=="R3" || R2=="R4" || R2=="R5")
		registerArray[reg1] = registerArray[reg1] + registerArray[reg2]; 
	else
		registerArray[reg1] = registerArray[reg1] + reg2;
}
// SUB ile karşılaşıldığın gönderilen registerların değerlerini çıkarır.
void sub(int registerArray[], string R1, string R2)
{
	int reg1=0,reg2=0;	
	
	reg1 = controlOfR(R1);
	reg2 = controlOfR(R2);
	
	if(R2=="R1" || R2=="R2" || R2=="R3" || R2=="R4" || R2=="R5")
		registerArray[reg1] = registerArray[reg1] - registerArray[reg2]; 
	else
		registerArray[reg1] = registerArray[reg1] - reg2;
}
//MOV ile karşılaşıldığında registerlara atama yapılır.
void mov(int registerArray[], string R1, string R2)
{
	int regValue=0;
	int reg1=0,reg2=0;	
	
	reg1 = controlOfR(R1);
	reg2 = controlOfR(R2);
	
	if(R2=="R1" || R2=="R2" || R2=="R3" || R2=="R4" || R2=="R5")
		registerArray[reg2] = registerArray[reg1]; 
	else
		registerArray[reg1] = reg2;
}
// Gönderilen registera göre hangi array kullanılacaksa onu return eder.
int controlOfR(string R)
{
	int temp;
	if(R=="R1")
		temp=0;
	else if(R=="R2")
		temp=1;
	else if(R=="R3")
		temp=2;
	else if(R=="R4")
		temp=3;
	else if(R=="R5")
		temp=4;
	else
		temp=stringToInt(R);
	return temp;
}
// Gönderilen text te geçen küçük harfleri büyük harflere çevirir.
string stringUpper(string text)
{
	int i=0;
	
	for(i=0; i<text.size(); i++)
		if(text[i] >= 'a' && text[i] <= 'z')
			text[i] = text[i] - 32; 
			
	return text;
}
// Gönderilen string i integer a çevirir.
int stringToInt(string str)
{
	int n = 0;
	for (int i = 0; i < str.size(); i += 1) 
	{
	    char digit = str.at(i);
    	if (digit < '0' || digit > '9')
      		return n;
    
    	n *= 10;
    	n += digit - '0';
	}
	return n;
}
