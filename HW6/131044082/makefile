all: _mainTester.cpp
	 g++ -std=c++11 _mainTester.cpp cpu.cpp cpuprogram.cpp memory.cpp computer.cpp -o exe
 
clean: 
	 rm -f all *.o exe
	
install: all
	 cp all /usr/bin
