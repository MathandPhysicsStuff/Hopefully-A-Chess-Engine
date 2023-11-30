#set noexpandtab

CC = gcc

CFLAGS = -O2 -lSDL2 -lSDL2main -lSDL2_ttf -lSDL2_image

all: bin

bin: main.o draw.o logic.o engine.o
	$(CC) $(CFLAGS) main.o draw.o logic.o engine.o -o bin

main.o: main.c
	$(CC) $(CFLACGS) -c main.c

draw.o: draw.c header.h
	$(CC) $(CFLACGS) -c draw.c

logic.o: logic.c header.h
	$(CC) $(CFLACGS) -c logic.c

engine.o: engine.c header.h
	$(CC) $(CFLACGS) -c engine.c

clean:
	rm -f *.o bin



