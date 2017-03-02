INCLUDE = -I../../shared/
GCC = g++
CPPFLAGS = -ggdb $(INCLUDE) -Wno-deprecated -std=c++11
CPPFLAGS += -O2 

OBJS = demo.o
LIBS = -L../../build -lshared -lpthread -lm -ldl -lpython2.7

all: demo	

demo :	$(OBJS)
	$(GCC) $(CPPFLAGS) -o $@ $^ $(LIBS) 
clean:
	rm *.o *.a demo -f
	rm log -rf

