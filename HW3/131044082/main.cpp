#include "cpuprog.h"
#include "cpu.h"

int main(int argc, char const *argv[])
{
	if (argc != 3)
	{
		cerr << "Faulty arguments !!" << endl;
		exit(1);
	}

	if(*argv[2] != '0' && *argv[2] != '1')
	{
		cerr << "Wrong option !!" << endl;
		exit(1);
	}

	CPUProg myProg(argv[1]);
	CPU myCpu(myProg.size(),0,1,argv[2]);


	while(!myCpu.halted())
	{
		string instruction = myProg.getLine(myCpu.getProgCounter());
		myCpu.execute(instruction);
	}

	return 0;
}