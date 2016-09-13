INCLUDE = -I../shared/ 
CXX = g++
GCC = g++
CPPFLAGS = -ggdb $(INCLUDE) -Wno-deprecated -std=c++11
CPPFLAGS += -O2 -DSERVER_INCLUDE_H

OBJS = main.o 
LIBS = -L../shared/ -lShare -lpthread -lm -ldl

all:	main

main:	$(OBJS)
	g++ -o $@ $^ $(LIBS)  
clean:
	rm *.o *.a -f

