netdriver.out: maxfinder.o NetDriver.o
	g++ -Wall  -ansi -o netdriver.out maxfinder.o NetDriver.o 

maxfinder.o: maxfinder.cpp NetDriver.h maxfinder.h computer.h
	g++ -Wall  -ansi -c maxfinder.cpp

NetDriver.o: NetDriver.cpp CPUTimer.h NetDriver.h maxfinder.h 
	g++ -Wall  -ansi -c NetDriver.cpp

clean:
	rm -f netdriver.out BinaryHeap.o maxfinder.o NetDriver.o 
