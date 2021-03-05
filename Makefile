objects = terminal.o people.o name.o services.o utilities.o

#Fair warning, dont totally understand these next two lines, 
#I stole them from the internet, so if anything bugs out, 
#look at these lines
#Also, now the test compilation uses gdb, 
#which is kinda annoying, so if anyone wants to fix... 
%.o: %.cpp  
	g++ -c -o $@ $< -g

ChocAn: ChocAn.o $(objects)
	g++ -g -o ChocAn ChocAn.o $(objects)
	rm *.o
	./ChocAn
	rm ChocAn
Test: Test.o $(objects)
	g++ -o Test Test.o $(objects)
	rm *.o
	./Test
	rm Test
