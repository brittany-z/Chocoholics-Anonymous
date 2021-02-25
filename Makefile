objects = terminal.o people.o name.o services.o utilities.o
includes = terminal.h people.h name.h services.h utilities.h
ChocAn: ChocAn.o $(objects)
	g++ -o ChocAn ChocAn.o $(objects)
	rm *.o
Test: Test.o $(objects)
	g++ -o Test Test.o $(objects)
	rm *.o
#$(objects) : $(includes)
