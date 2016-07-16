include ../Makefile.Define
INCLUDE = -I./
OBJS = Config.o Log.o Epoll_Engine.o TcpSocket.o Mutex.o \
	   Buffer.o Encryption.o MemoryPool.o Random.o \
	   Locker.o Min_Heap.o SigEventMgr.o TimeManager.o\
	   mm_Thread.o mm_ThreadPool.o mm_Task.o

all:	libShare.a

libShare.a:	$(OBJS)
	ar cru $@ $(OBJS)
	ranlib $@

clean:
	rm *.o *.a -f

install:
	cp libshared.a ../../libshared-0.0.1-release/ -f
