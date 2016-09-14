INCLUDE = -I../../shared/
GCC = g++
CPPFLAGS = -O2 -ggdb $(INCLUDE) -Wno-deprecated -std=c++11
OBJS = time-task.o
LIBS = -L../../build -lshared -lpthread -lm -ldl

all : time-task

time-task : $(OBJS) 
	$(GCC) -o $@ $^ $(LIBS)

clean :
	rm -rf *.o time-task log/
