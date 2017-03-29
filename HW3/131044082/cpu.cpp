#include "cpu.h"

using namespace std;

int CPU::progCounter = 1;

CPU::CPU(int fileSize, int value, int firstProgCounter, string opt)
{
	size = fileSize;
	option = opt;
	setRegister(0, value);
	setRegister(1, value);
	setRegister(2, value);
	setRegister(3, value);
	setRegister(4, value);
	setProgCounter(firstProgCounter);
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

void CPU::print()const
{
	for (int i=0; i<5; ++i)
		cout << "R" << i+1 << "=" << registers[i] << " ";
	cout << endl;
	cout << "PC=" << progCounter << endl;
}

bool CPU::halted()const
{
	if(getProgCounter() >= (size+1))
		return true;
}

void CPU::execute(string text)
{
	string instruction, r1, r2;
	text = stringUpper(text);
	instructionControl(text, instruction, r1, r2);
	if(option == "1")
	{
		cout << instruction << " " << r1 << "," << r2 << endl;
		print(); 
	}
    if(instruction == "MOV")	
		mov(r1, r2);      
    else if(instruction == "ADD")
		add(r1, r2);
    else if(instruction == "SUB")
		sub(r1, r2);
    else if(instruction == "PRN")
   	{
   		printReg(r1);
    }
    else if(instruction == "JMP")
    {
    	int temp=0,reg=0, reg1=0;
    	reg = controlOfR(r1);
		reg1 = controlOfR(r2);
		temp = registers[reg];

  		if(stringToInt(r2) != 0)	// JMP R1, 3 şeklindeki komutun
		{							// çalışması burada kontrol ediliyor.
			if(temp == 0)
				jmp(r2);
				
		}	
		else if(stringToInt(r2) == 0)	// JMP 2 şeklindeki komutun kontrolü burada yapılıyor.
			jmp(r1);

    }
    else if(instruction == "HLT")
    {
    	print();
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

void CPU::jmp(string lineNumber)
{
	int lineN = stringToInt(lineNumber);
	setProgCounter(lineN-1);
}

void CPU::printReg(string R) 
{
	int reg = controlOfR(R);
	if(reg > sizeof(registers))
	{
		cerr << "Faulty register!!" << endl;
		exit(1);
	}
	cout << "R" << reg+1 << "=" << registers[reg] << endl;
}

// ADD ile karşılaşıldığın gönderilen registerların değerlerini topla.
void CPU::add(string R1, string R2)
{
	int reg1=0,reg2=0,temp1=0,temp2=0;	
	
	reg1 = controlOfR(R1);
	reg2 = controlOfR(R2);

	
	if(R2=="R1" || R2=="R2" || R2=="R3" || R2=="R4" || R2=="R5")
	{
		temp1 = getRegister(reg1);
		temp2 = getRegister(reg2);
		temp1 += temp2;
		setRegister(reg1,temp1);
	}
	else
	{
		temp1 = getRegister(reg1);
		temp1 += reg2;
		setRegister(reg1,temp1);
	}
}
// SUB ile karşılaşıldığın gönderilen registerların değerlerini çıkarır.
void CPU::sub(string R1, string R2)
{
	int reg1=0,reg2=0,temp1=0, temp2=0;	
	
	reg1 = controlOfR(R1);
	reg2 = controlOfR(R2);
	
	if(R2=="R1" || R2=="R2" || R2=="R3" || R2=="R4" || R2=="R5")
	{
		temp1 = getRegister(reg1);
		temp2 = getRegister(reg2);
		temp1 -= temp2;
		setRegister(reg1,temp1);
	}
	else
	{
		temp1 = getRegister(reg1);
		temp1 -= reg2;
		setRegister(reg1,temp1);
	}
}
//MOV ile karşılaşıldığında registerlara atama yapılır.
void CPU::mov(string R1, string R2)
{
	int regValue=0;
	int reg1=0,reg2=0,temp=0;;	
	
	reg1 = controlOfR(R1);
	reg2 = controlOfR(R2);
	
	if(R2=="R1" || R2=="R2" || R2=="R3" || R2=="R4" || R2=="R5")
	{
		temp = getRegister(reg1);
		setRegister(reg2,temp); 
	}
	else
	{
		setRegister(reg1,reg2);
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