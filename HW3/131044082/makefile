all: main.cpp
	 g++ -std=c++11 main.cpp cpu.cpp cpuprog.cpp -o exe
 
clean: 
	 rm -f all *.o
	
install: all
	 cp all /usr/bin
