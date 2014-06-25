CC=g++
CFLAGS= -Wall -c
LIBS= -lsfml-graphics -lsfml-system -lsfml-window
OBJ= main.o DisplayBlock.o TetrisPiece.o Point.o TetrisBlock.o TetrisGame.o TetrisGrid.o TetrisScore.o
SRC=../src

all: tetris

tetris: $(OBJ)
	$(CC) $(OBJ) -o tetris $(LIBS)
	mkdir tetris-game
	mv tetris tetris-game
	cp -R ../images tetris-game

%.o: $(SRC)/%.cpp
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm ./*.o
	rm -rf tetris-game
