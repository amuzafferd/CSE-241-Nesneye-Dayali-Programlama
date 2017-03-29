/*				AHMET MUZAFFER DÜLGER
					  13104082
			 SON GÜNCELLEME: 15.10.2016
*/

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstdint>

using namespace std;

//Fonksiyon prototipleri
string stringUpper(string text);
void instructionControl(string text, string& instruction, string& r1, string& r2);
int controlOfR(string R);
int stringToInt(string str);
void hlt(int registerArray[], uint8_t memory[]);
void mov(int registerArray[], uint8_t memory[], string R1, string R2);
void prn(int registerArray[], uint8_t memory[], string ins, string R, string text, int argvValue);
void add(int registerArray[], uint8_t memory[], string R1, string R2);
void sub(int registerArray[], uint8_t memory[], string R1, string R2);

int main(int argc, char const *argv[])
{
	fstream inputFile;
	uint8_t memory[50] = {0};
	int registers[5] = {0};
	string text, instruction, r1, r2;

	// Konsoldan girilen değerlerin sayısının 3 olması kontrolü
	if(argc != 3)
	{
		cerr << "Fault arguments !!" << endl;
		exit(1);
	}
	// Option kontrolü
	if(*argv[2] != '0' && *argv[2] != '1' && *argv[2] != '2')
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

	while(!inputFile.eof())
    {
        getline(inputFile, text);

        text = stringUpper(text); //okunan komutlar büyük harfe çevrilir.
		
		instructionControl(text,instruction,r1,r2); /*instruction, r1, r2
													  kontrolleri yapılıyor.*/
        
        if(instruction == "MOV")
        {	
        	mov(registers, memory, r1, r2);
        	prn(registers, memory, instruction, r1, text, argValue);
        }
        else if(instruction == "ADD")
        {
        	add(registers, memory, r1, r2);
        	prn(registers, memory, instruction, r1, text, argValue);
        }
        else if(instruction == "SUB")
        {
        	sub(registers, memory, r1, r2);
        	prn(registers, memory, instruction, r1, text, argValue);
        }	
        else if(instruction == "PRN")
        	prn(registers, memory, instruction, r1, text, argValue);
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
			prn(registers, memory, instruction, r1, text, argValue);
        }
        else if (instruction == "JPN") // JPN R2, 16
        {
        	int temp=0,reg=0;
			reg = controlOfR(r1);
			temp = registers[reg];
			
			if(temp <= 0)
			{
				inputFile.close();
				inputFile.open(argv[1]);
				for(int i=0; i<stringToInt(r2)-1;++i)
					getline(inputFile, text);					
			}
			prn(registers, memory, instruction, r1, text, argValue);
        }				
		else if(instruction == "HLT")
        {
			prn(registers, memory, instruction, r1, text, argValue);
			hlt(registers,memory);	
			exit(1);
		}
		else
		{
			cerr << "Fauly instruction!!" << endl;
			exit(1);
		}
		
		instruction.clear();
        r1.clear();
        r2.clear();
    }

    inputFile.close();
    return 0;
}

void instructionControl(string text, string& instruction, string& r1, string& r2)
{
	int i=0; int j=0;

	while(text[i] != '\0' && text[i] != ';')
	{	//instruction kontrolü yapılıyor.
		if (text[i] == 'M' || text[i] == 'A' || text[i] == 'S' ||
	        text[i] == 'J' || text[i] == 'H' || text[i] == 'P')
     	{
        	if(text[i+1] == ' ' || text[i+2] == ' ')
        	{
        		cerr << "Faulty instruction!!" << endl;
        		exit(1);
        	}
        	else
        	{
        		while(j<3)
        		{
        			instruction += text[i];
        			j++;
        			i++;
        		}
        	}
        }
        else if (text[i] != ' ' && j==3)
        {	//r1 kontrolü yapılıyor.
        	while(text[i] != ',' && text[i] != '\0' && text[i] != ';')
        	{
        		r1 += text[i];
        		i++;
        		j=4;
        	}
        }
        else if (text[i] != ',' && text[i] != ' ' && j==4)
        {	//r2 kontrolü yapılıyor.
        	r2 += text[i];
        	i++;
        }
        else
			i++;
	}
}
//Getline ile okunan text i büyük harfe çevirip return ediyor. 
string stringUpper(string text)
{
	int i=0;
	
	for(i=0; i<text.size(); i++)
		if(text[i] >= 'a' && text[i] <= 'z')
			text[i] = text[i] - 32; 
			
	return text;
}
//Gelen string e göre hangi arrayin kullanılacağı, constant ise
//constant değer return ediliyor.
int controlOfR(string R)
{
	int temp; 
	string strTemp;
	if(R[0]== 'R' && R[1]== '1')
		temp=0;
	else if(R[0]== 'R' && R[1]== '2')
		temp=1;
	else if(R[0]== 'R' && R[1]== '3')
		temp=2;
	else if(R[0]== 'R' && R[1]== '4')
		temp=3;
	else if(R[0]== 'R' && R[1]== '5')
		temp=4;
	else if(R[0]== '#')
	{
		int i=1;
		while(R[i] != '\0')
			strTemp += R[i++];
		temp=stringToInt(strTemp);
	}
	else
		temp=stringToInt(R);
	return temp;
}
//Gönderilen string i integer a çeviriyor.
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

void mov(int registerArray[], uint8_t memory[], string R1, string R2)
{
	int reg1=0,reg2=0;
	string temp;	
	
	if(R1[0]=='R')
	{
		if (R2[0] == '#') //MOV R1, #3
		{
			int i=1;
			while(R2[i] != '\0')
			{
				temp+=R2[i];
				i++;
			}
			reg1 = controlOfR(R1);
			reg2 = controlOfR(temp);
			memory[reg2] = registerArray[reg1];
		}
		else if(R2[0] == 'R') //MOV R1, R2
		{
			reg1 = controlOfR(R1);
			reg2 = controlOfR(R2);
			registerArray[reg2] = registerArray[reg1]; 
		}
		else //MOV R1, 3
		{
			reg1 = controlOfR(R1);
			reg2 = controlOfR(R2);
			registerArray[reg1] = reg2;
		}
	}
	else if(R1[0] == '#')
	{
		int i=1;
		while(R1[i] != '\0') 
		{
			temp+=R1[i];
			i++;
		}
		if (R2[0] == 'R') //MOV #3, R1
		{
			reg1 = controlOfR(R2);
			reg2 = controlOfR(temp);
			registerArray[reg1] = memory[reg2];
		}
		else //MOV #3, 3
		{
			reg1 = controlOfR(temp);
			reg2 = controlOfR(R2);
			memory[reg1] = reg2;
		}
	}	
}

void add(int registerArray[], uint8_t memory[], string R1, string R2)
{
	int reg1=0,reg2=0;	
	string temp, temp2;
	
	if(R1[0]=='R')
	{
		if (R2[0] == '#') //ADD R1, #3
		{
			int i=1;
			while(R2[i] != '\0')
			{
				temp+=R2[i];
				i++;
			}
			reg1 = controlOfR(R1);
			reg2 = controlOfR(temp);
			registerArray[reg1] += memory[reg2];
		}
		else if(R2[0] == 'R') //ADD R1, R2
		{			 
			reg1 = controlOfR(R1);
			reg2 = controlOfR(R2);
			registerArray[reg1] += registerArray[reg2];
		}
		else //ADD R1, 3
		{
			reg1 = controlOfR(R1);
			reg2 = controlOfR(R2);			
			registerArray[reg1] += reg2;
		}
	}
	else if(R1[0] == '#')
	{
		int i=1;
		while(R1[i] != '\0')
		{
			temp+=R1[i];
			i++;
		}
		if (R2[0] == '#') //ADD #3, #4
		{
			int i=1;
			while(R2[i] != '\0')
			{
				temp2+=R2[i];
				i++;
			}
			reg1 = controlOfR(temp);
			reg2 = controlOfR(temp2);
			memory[reg1] += memory[reg2];
		}
		else if (R2[0] == 'R') //ADD #3, R1
		{
			reg1 = controlOfR(R1);
			reg2 = controlOfR(temp);
			memory[reg2] += registerArray[reg1];
		}
		else //ADD #3, 3
		{
			reg1 = controlOfR(temp);
			reg2 = controlOfR(R2);
			memory[reg1] += reg2;
		}
	}	
}

void sub(int registerArray[], uint8_t memory[], string R1, string R2)
{
	int reg1=0,reg2=0;	
	string temp, temp2;
	
	if(R1[0]=='R')
	{
		if (R2[0] == '#') //SUB R1, #3
		{
			int i=1;
			while(R2[i] != '\0')
			{
				temp+=R2[i];
				i++;
			}
			reg1 = controlOfR(R1);
			reg2 = controlOfR(temp);
			registerArray[reg1] -= memory[reg2];
		}
		else if(R2[0] == 'R') //SUB R1, R2
		{ 
			reg1 = controlOfR(R1);
			reg2 = controlOfR(R2);
			registerArray[reg1] -= registerArray[reg2];
		}
		else //SUB R1, 3
		{
			reg1 = controlOfR(R1);
			reg2 = controlOfR(R2);			
			registerArray[reg1] -= reg2;
		}
	}
	else if(R1[0] == '#')
	{
		int i=1;
		while(R1[i] != '\0')
		{
			temp+=R1[i];
			i++;
		}
		if (R2[0] == '#') //SUB #3 , #4
		{
			int i=1;
			while(R2[i] != '\0')
			{
				temp2+=R2[i];
				i++;
			}
			reg1 = controlOfR(temp);
			reg2 = controlOfR(temp2);
			memory[reg1] -= memory[reg2];
		}
		else if (R2[0] == 'R') //SUB #3, R1
		{
			reg1 = controlOfR(R1);
			reg2 = controlOfR(temp);
			memory[reg2] -= registerArray[reg1];
		}
		else //SUB #3, 3
		{
			reg1 = controlOfR(temp);
			reg2 = controlOfR(R2);
			memory[reg1] -= reg2;
		}
	}	
}

void hlt(int registerArray[], uint8_t memory[])
{
    int i;
    for(i=0; i<5; i++)
		cout << "R" << i+1 << "=" << registerArray[i] << " " ;
	cout << endl;
	for (int i = 0; i < 50; ++i)
    	cout << "M" << i << "=" << (unsigned)memory[i] << " ";
    cout << endl;
}

void prn(int registerArray[], uint8_t memory[], string ins, string R, string text, int argvValue)
{
	int reg=0;
	string temp;
	if(argvValue == 0 && ins == "PRN") //Option 0 ise
	{
		if(R[0] == '#')
		{
			int i=1;
			while(R[i] != '\0')
			{
				temp+=R[i];
				i++;
			}
			reg = controlOfR(temp);
			cout << "M" << reg << "=" << (unsigned)memory[reg] << endl;
		}
		else
		{		
			reg=controlOfR(R);
		
			if(R[0] == 'R')
				cout << "R" << reg+1 << "=" << registerArray[reg] << endl;
			else
				cout << "R" << reg << "=" << reg << endl;
		}
	}
	else if(argvValue == 1) //Option 1 ise
	{
		for(int i=0; i<5; i++)
			cout << "R" << i+1 << "=" << registerArray[i] << " " ;
		cout << endl;
		for(int i=0; text[i] != ';' && text[i] != '\0' ; i++)
			cout << text[i];
		cout << endl;
	}	
	else if (argvValue == 2) //Option 2 ise
	{
		for(int i=0; i<5; i++)
			cout << "R" << i+1 << "=" << registerArray[i] << " " ;
		cout << endl;
		for (int i = 0; i<50; i++)
			cout << "M" << i << "=" << (unsigned)memory[i] << " ";
		cout << endl;
		for(int i=0; text[i] != ';' && text[i] != '\0' ; i++)
			cout << text[i];
		cout << endl;
	}
}