CXX = g++
INCLUDE = -I../../shared/
CPPFLAGS = -ggdb $(INCLUDE) -Wno-deprecated -O2 -std=c++11
LIBS = -L../../build/ -L/usr/lib64/mysql -lshared -lpython2.7 -lmysqlclient
OBJECTS = main.o LoginSocket.o User.o Mail.o MysqlOperate.o

all : ManagerServer

ManagerServer : $(OBJECTS)
	$(CXX) $(CPPFLAGS) -o $@ $^ $(LIBS) 

clean:
	rm -rf *.o ManagerServer


