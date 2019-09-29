CXX = g++
CXXFLAGS = -std=c++11 -Wall

OBJECTS = parse.o param.o

all: myshell slow

myshell:  myshell.o $(OBJECTS)
		$(CXX) $(CXXFLAGS) -o $@ $^

	
slow:  slow.o 
		$(CXX) $(CXXFLAGS) -o $@ $^

# g++ -std=c++11 -Wall slow.cpp -o slow 
		
clean:
		$(RM) *.o myshell slow
