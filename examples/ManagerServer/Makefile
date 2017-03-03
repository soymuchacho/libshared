CXX = g++
INCLUDE = -I../../shared/
CPPFLAGS = -ggdb $(INCLUDE) -Wno-deprecated -O2 -std=c++11
LIBS = -L../../build/ -lshared -lpython2.7
OBJECTS = main.o LoginSocket.o User.o Mail.o

all : ManagerServer

ManagerServer : $(OBJECTS)
	$(CXX) $(CPPFLAGS) -o $@ $^ $(LIBS) 

clean:
	rm -rf *.o ManagerServer


