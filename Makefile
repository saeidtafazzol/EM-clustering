OPENCV = `pkg-config opencv --cflags --libs`

LIBS = $(OPENCV)
CC = g++
CFLAGS = -c

all: em


em: Cluster.o Color.o EM.o main.o
		$(CC) main.o EM.o Color.o Cluster.o -o em $(LIBS) -O1 -larmadillo

main.o: main.cpp
		$(CC) $(CFLAGS) main.cpp $(LIBS)	-O1 -larmadillo

Color.o: Color.cpp
		$(CC) $(CFLAGS) Color.cpp $(LIBS) -O1 -larmadillo

EM.o: EM.cpp
		$(CC) $(CFLAGS) EM.cpp $(LIBS) -O1 -larmadillo

Cluster.o: Cluster.cpp
		$(CC) $(CFLAGS) Cluster.cpp $(LIBS) -O1 -larmadillo

clean:
	 rm *o em
