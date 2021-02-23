objects = ChocAn.o terminal.o people.o name.o services.o utilities.o
includes = terminal.h people.h name.h services.h utilities.h
ChocAn: $(objects)
	g++ -o ChocAn $(objects)
	rm *.o
$(objects) : $(includes)
