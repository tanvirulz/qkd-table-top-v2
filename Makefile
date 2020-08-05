# Sorry for the super messy version of makefile (  that works for now. )
# Definitely have to learn how to write a smarter one.

CC=g++
IFLAGS=-I /usr/include/timetagger
LFLAGS=-l TimeTagger 


ODIR=./obj


# nominal compile
#default: mkobjdir nondeb mem reg  proc $(SDIR)/main.c 
#	gcc -o run $(ODIR)/memory.o $(ODIR)/registers.o  $(ODIR)/debug.o $(ODIR)/processor.o $(SDIR)/main.c $(IFLAGS) 
default: readRawSwabian.cpp correctTimestamp.cpp coinmatch.cpp sifting.cpp
	$(CC) -o rrswabian readRawSwabian.cpp $(IFLAGS) $(LFLAGS)
	$(CC) -o crt correctTimestamp.cpp 
	$(CC) -o cm coinmatch.cpp 
	$(CC) -o sift sifting.cpp

rrswabian: readRawSwabian.cpp
	$(CC) -o rrswabian readRawSwabian.cpp $(IFLAGS) $(LFLAGS)

crt: correctTimestamp.cpp
	$(CC) -o crt correctTimestamp.cpp 

cm: coinmatch.cpp
	$(CC) -o cm coinmatch.cpp 

sift: sifting.cpp
	$(CC) -o sift sifting.cpp

run: default run.sh
	./run.sh /home/tanvir/work/Programming/gProj/qkd-table-top-v2/swabian/20200803_swabian_highres_highcount 1_9mW0dB.1.ttbin 03Aug result.csv 1500

runbatch: default runbatch.py run.sh
	python3 runbatch.py
clean:
	rm -f rrswabian
	rm -f crt 
	rm -f cm 
	rm -f sift 


