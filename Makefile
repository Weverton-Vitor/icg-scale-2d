CC = g++

all:
	$(CC) main.cpp -lglut -lGLU -lGL -I. -o main

clean:
	rm main
