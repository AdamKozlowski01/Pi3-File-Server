CC = g++

default: server

# To create the executable file count we need the object files
# server.o, ConnectionHandler.o, ConnectionFactory.o, and ThreadPool.o:
#
server: server.o ConnectionHandler.o ConnectionFactory.o ThreadPool.o
	$(CC) $(CFLAGS) -o PiFiServer server.o ConnectionHandler.o ConnectionFactory.o ThreadPool.o

# To create the object file server.o, we need the source
# files server.cpp, ConnectionHandler.h, ThreadPool.h:
#
server.o:  server.cpp ConnectionHandler.h ThreadPool.h 
	$(CC) $(CFLAGS) -c server.cpp 

# To create the object file ConnectionHandler.o, we need the source files
# ConnectionHandler.cpp ConnectionFactory.h ThreadPool.h:
#
ConnectionHandler.o:  ConnectionHandler.cpp ConnectionFactory.h ThreadPool.h
	$(CC) $(CFLAGS) -c ConnectionHandler.cpp

# To create the object file scanner.o, we need the source files
# scanner.c and scanner.h:
#
ConnectionFactory.o:  ConnectionFactory.cpp ThreadPool.h
	$(CC) $(CFLAGS) -c ConnectionFactory.cpp

ThreadPool.o: ThreadPool.cpp
	$(CC) $(CFLAGS) -c ThreadPool.cpp

# To start over from scratch, type 'make clean'.  This
# removes the executable file, as well as old .o object
# files and *~ backup files:
#
clean: 
	$(RM) server *.o *~
