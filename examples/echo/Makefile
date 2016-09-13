INCLUDE = -I../../shared/ 
GCC = g++
CPPFLAGS = -ggdb $(INCLUDE) -Wno-deprecated -std=c++11
CPPFLAGS += -O2 

OBJS = EchoSocket.o echo.o
LIBS = -L../../build -lshared -lpthread -lm -ldl

all:	echo

echo:	$(OBJS)
	$(GCC) $(CPPFLAGS) -o $@ $^ $(LIBS) 
clean:
	rm *.o *.a echo -f
	rm log -rf

