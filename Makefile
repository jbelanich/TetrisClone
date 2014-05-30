CC=g++
CFLAGS= -Wall -c
LIBS= -lsfml-graphics -lsfml-system -lsfml-window

all: tetris

tetris: main.o DisplayBlock.o Piece.o Point.o TetrisBlock.o TetrisGame.o TetrisGrid.o TetrisScore.o
	$(CC) main.o DisplayBlock.o Piece.o Point.o TetrisBlock.o TetrisGame.o TetrisGrid.o TetrisScore.o -o tetris $(LIBS)

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp -o main.o

DisplayBlock.o: DisplayBlock.cpp
	$(CC) $(CFLAGS) DisplayBlock.cpp -o DisplayBlock.o

Piece.o: Piece.cpp
	$(CC) $(CFLAGS) Piece.cpp -o Piece.o

Point.o: Point.cpp
	$(CC) $(CFLAGS) Point.cpp -o Point.o

TetrisBlock.o: TetrisBlock.cpp
	$(CC) $(CFLAGS) TetrisBlock.cpp -o TetrisBlock.o

TetrisGame.o: TetrisGame.cpp
	$(CC) $(CFLAGS) TetrisGame.cpp -o TetrisGame.o

TetrisGrid.o: TetrisGrid.cpp
	$(CC) $(CFLAGS) TetrisGrid.cpp -o TetrisGrid.o

TetrisScore.o: TetrisScore.cpp
	$(CC) $(CFLAGS) TetrisScore.cpp -o TetrisScore.o

clean:
	rm ./*.o
	rm ./tetris
