/*
 *  TetrisGame.h
 *  Tetris
 *
 *  Created by Joshua Belanich.
 */

#ifndef _TETRISGAME_
#define _TETRISGAME_
#include "TetrisGrid.h"
#include "Piece.h"
#include "TetrisScore.h"
#include "TetrisBlock.h"
#include "DisplayBlock.h"
#include <SFML/Graphics.hpp>

class TetrisGame {
private:
	
	TetrisGrid grid;
	Piece currentPiece;
	Piece nextPiece;
	TetrisScore scoreBoard;
	sf::RenderWindow App;
	float timePerMove;
	bool running;
	
	void displayNextBlock();
	void rotateIfPossible();
	void moveIfPossible(Point direction);
	void drop();
	void fallAllTheWay();
	
	void testLose();
	
public:
	
	void initGame();
	void closeGame();
	int gameLoop();
	
};
#endif