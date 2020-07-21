# Sorry for the super messy version of makefile (  that works for now. )
# Definitely have to learn how to write a smarter one.

CC=g++
IFLAGS=-I /usr/include/timetagger
LFLAGS=-l TimeTagger 


ODIR=./obj


# nominal compile
#default: mkobjdir nondeb mem reg  proc $(SDIR)/main.c 
#	gcc -o run $(ODIR)/memory.o $(ODIR)/registers.o  $(ODIR)/debug.o $(ODIR)/processor.o $(SDIR)/main.c $(IFLAGS) 
default:
	$(CC) -o rrswabian readRawSwabian.cpp $(IFLAGS) $(LFLAGS)
	$(CC) -o crt correctTimestamp.cpp 
	$(CC) -o cm coinmatch.cpp 
	$(CC) -o sift sifting.cpp

rrswabian:
	$(CC) -o rrswabian readRawSwabian.cpp $(IFLAGS) $(LFLAGS)

crt:
	$(CC) -o crt correctTimestamp.cpp 

cm:
	$(CC) -o cm coinmatch.cpp 

sift:
	$(CC) -o sift sifting.cpp

run: default
	./run.sh ./swabian/20200714_Swabian_Timestamp/data_2 4_1uW0dB.1.ttbin 14july0db result.csv
	
clean:
	rm -f rrswabian
	rm -f crt 
	rm -f cm 
	rm -f sift 


