CC=gcc

SOURCES=./src/dataUsage.c ./src/resources.c ./src/datausageaboutwin.c ./src/datausageapp.c ./src/datausagewin.c ./src/main.c
EXECUTABLE=./src/lion
CFLAGS=`pkg-config --cflags gtk+-3.0`
CFLAGSS=`pkg-config --libs gtk+-3.0`

all: $(SOURCES)
	$(CC) $(SOURCES) $(CFLAGS) -o $(EXECUTABLE) $(CFLAGSS)