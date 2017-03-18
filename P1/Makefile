deque.out : dequeRunner.o mynew.o  
	g++ -ansi -Wall -g -o deque.out dequeRunner.o mynew.o  

dequeRunner.o : dequeRunner.cpp deque.h mynew.h CPUTimer.h deque.cpp
	g++ -ansi -Wall -g -c dequeRunner.cpp

mynew.o : mynew.cpp mynew.h 
	g++ -ansi -Wall -g -c mynew.cpp

clean : 
	rm -f deque.out dequeRunner.o  mynew.o   
