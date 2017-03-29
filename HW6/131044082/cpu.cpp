/*				AHMET MUZAFFER DÜLGER
					  13104082
			 SON GÜNCELLEME: 16.11.2016
*/

#include "cpu.h"

using namespace std;

int CPU::progCounter = 1;

CPU::CPU(int opt)
{
	if(opt != 0 && opt != 1 && opt != 2)
	{
		cerr << "Wrong option !!" << endl;
		exit(1);
	}
	setOption(opt);
}

CPU::CPU()
{
	setOption(0);
}

void CPU::setRegister(int index, int value)
{
	registers[index] = value;
}

int CPU::getRegister(int index)const
{
	return registers[index];
}

void CPU::setProgCounter(int firstProgCounter)
{
	progCounter = firstProgCounter;
}

int CPU::getProgCounter()const
{
	return progCounter;
}

int CPU::getOption()const
{
	return option;
}

void CPU::setOption(int opt)
{
	option = opt;
}

void CPU::print()const
{
	for (int i=0; i<5; ++i)
		cout << "R" << i+1 << "=" << registers[i] << " ";
	cout << endl;
	cout << "PC=" << progCounter+1 << endl;
}

bool CPU::halted()const
{
	if(getProgCounter() == getSize()+1)
		return true;
}

void CPU::execute(string text, Memory& myMem)
{
	string instruction, r1, r2;
	text = stringUpper(text);
	instructionControl(text, instruction, r1, r2);
    if(instruction == "MOV")	
		mov(r1, r2, myMem);      
    else if(instruction == "ADD")
		add(r1, r2, myMem);
    else if(instruction == "SUB")
		sub(r1, r2, myMem);
    else if(instruction == "PRN")
   		printReg(r1, myMem);
    else if(instruction == "JMP")
    {
    	int temp=0,reg=0, reg1=0;
    	reg = controlOfR(r1);
		reg1 = controlOfR(r2);
		temp = getRegister(reg);

  		if(stringToInt(r2) != 0)	// JMP R1, 3 şeklindeki komutun
		{							// çalışması burada kontrol ediliyor.
			if(temp == 0)
				jmp(r2);
				
		}	
		else if(stringToInt(r2) == 0)	// JMP 2 şeklindeki komutun kontrolü burada yapılıyor.
			jmp(r1);

    }
    else if(instruction == "JPN")
    {
    	int reg;
    	reg = controlOfR(r1);
    	if(getRegister(reg) <= 0)
    		jpn(r2);
    }
    else if(instruction == "HLT")
    {
    	cout << "---------------------------------------------" << endl;
    	myMem.printAll();
    	print();
    	cout << "---------------------------------------------" << endl;
	}

	if(getOption() == 1)
	{
		cout << text << endl;
		print();
	}
	else if(getOption() == 2)
	{
		cout << text << endl;
		print();
		myMem.printAll();
	}
	setProgCounter(getProgCounter()+1);
}

// Gönderilen stringten instruction ve registerların değerleri çeker.
void CPU::instructionControl(string text, string& instruction, string& r1, string& r2)
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
// JMP ile karşışaışdığında istenilen satıra atlar.
void CPU::jmp(string lineNumber)
{
	int lineN = stringToInt(lineNumber);
	setProgCounter(lineN-1);
}
// JPN ile karşışaışdığında istenilen satıra atlar.
void CPU::jpn(string lineNumber)
{
	int lineN = stringToInt(lineNumber);
	setProgCounter(lineN-1);
}

void CPU::printReg(string R, Memory& memory)
{
	if(R[0] == '#')
	{
		int i=1;
		string temp;
		while(R[i] != '\0')
		{
			temp+=R[i];
			i++;
		}
		int reg = controlOfR(temp);
		if(reg > sizeof(registers))
		{
			cerr << "Faulty register!!" << endl;
			exit(1);
		}
		cout << "[" << reg << "] -> " << memory.getMemory(reg) << endl;
	}
	else
	{
		int reg = controlOfR(R);
		if(reg > sizeof(registers))
		{
			cerr << "Faulty register!!" << endl;
			exit(1);
		}
		
		cout << "R" << reg+1 << "=" << registers[reg] << endl;
	}
}

//ADD ile karşılaşıldığında gönderilen registerların veya memorylerin değerlerini topla.
void CPU::add(string R1, string R2, Memory& memory)
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
			setRegister(reg1,(getRegister(reg1) + memory.getMemory(reg2)));
		}
		else if(R2[0] == 'R') //ADD R1, R2
		{			 
			reg1 = controlOfR(R1);
			reg2 = controlOfR(R2);
			setRegister(reg1,(getRegister(reg1) + getRegister(reg2)));
		}
		else //ADD R1, 3
		{
			reg1 = controlOfR(R1);
			reg2 = controlOfR(R2);	
			setRegister(reg1,(getRegister(reg1) + reg2));		
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
			memory.setMemory(reg1,(memory.getMemory(reg1) + memory.getMemory(reg2)));
		}
		else if (R2[0] == 'R') //ADD #3, R1
		{
			reg1 = controlOfR(R1);
			reg2 = controlOfR(temp);
			memory.setMemory(reg2,(memory.getMemory(reg2) + getRegister(reg1)));
		}
		else //ADD #3, 3
		{
			reg1 = controlOfR(temp);
			reg2 = controlOfR(R2);
			memory.setMemory(reg1,(memory.getMemory(reg1) + reg2));
		}
	}	
}
//SUB ile karşılaşıldığında gönderilen registerların veya memorylerin değerlerini çıkarır.
void CPU::sub(string R1, string R2, Memory& memory)
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
			setRegister(reg1,(getRegister(reg1) - memory.getMemory(reg2)));
		}
		else if(R2[0] == 'R') //SUB R1, R2
		{ 
			reg1 = controlOfR(R1);
			reg2 = controlOfR(R2);					
			setRegister(reg1,(getRegister(reg1) - getRegister(reg2)));
		}
		else //SUB R1, 3
		{
			reg1 = controlOfR(R1);
			reg2 = controlOfR(R2);		
			setRegister(reg1,(getRegister(reg1) - reg2));			
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
			memory.setMemory(reg1,(memory.getMemory(reg1) - memory.getMemory(reg2)));
		}
		else if (R2[0] == 'R') //SUB #3, R1
		{
			reg1 = controlOfR(R1);
			reg2 = controlOfR(temp);	
			memory.setMemory(reg2,(memory.getMemory(reg2) - getRegister(reg1)));
		}
		else //SUB #3, 3
		{
			reg1 = controlOfR(temp);
			reg2 = controlOfR(R2);	
			memory.setMemory(reg1,(memory.getMemory(reg1) - reg2));
		}
	}	
}
//MOV ile karşılaşıldığında registerlara veya memorye atama yapılır.
void CPU::mov(string R1, string R2, Memory& memory)
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
			memory.setMemory(reg2, getRegister(reg1));
		}
		else if(R2[0] == 'R') //MOV R1, R2
		{
			reg1 = controlOfR(R1);
			reg2 = controlOfR(R2);
			setRegister(reg2, getRegister(reg1));
		}
		else //MOV R1, 3
		{
			reg1 = controlOfR(R1);
			reg2 = controlOfR(R2);
			setRegister(reg1, reg2);
		}
	}
	else if(R1[0] == '#')
	{
		int i=1;
		while(R1[i] != ',') 
		{
			temp+=R1[i];
			i++;
		}
		if (R2[0] == 'R') //MOV #3, R1
		{
			reg1 = controlOfR(R2);
			reg2 = controlOfR(temp);
			setRegister(reg1, (int)memory.getMemory(reg2));
		}
		else //MOV #3, 3
		{
			reg1 = controlOfR(temp);
			reg2 = controlOfR(R2);
			memory.setMemory(reg1, reg2);
		}
	}	
}
// Gönderilen registera göre hangi array kullanılacaksa onu return eder.
int CPU::controlOfR(string R)
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
string CPU::stringUpper(string text)
{
	int i=0;
	
	for(i=0; i<text.size(); i++)
		if(text[i] >= 'a' && text[i] <= 'z')
			text[i] = text[i] - 32; 
			
	return text;
}
// Gönderilen string i integer a çevirir.
int CPU::stringToInt(string str)
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

void CPU::setSize(int newSize)
{
	size = newSize;
}

int CPU::getSize()const
{
	return size;
}