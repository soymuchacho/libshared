INCLUDE = -I../../shared/ 
GCC = g++
CPPFLAGS = -ggdb $(INCLUDE) -Wno-deprecated -std=c++11
CPPFLAGS += -O2 

OBJS = day-time.o TimeSocket.o 
LIBS = -L../../build/ -lshared -lpthread -lm -ldl

all:	daytime client

daytime:	$(OBJS)
	$(GCC) -o $@ $^ $(LIBS)  

client: client.o
	$(GCC) -o $@ $^ $(LIBS)  

clean:
	rm *.o *.a client daytime log/ -rf

