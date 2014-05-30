/*
 *  Piece.h
 *  Tetris
 *
 *  Created by Joshua Belanich.
 */


#ifndef _PIECE_
#define _PIECE_

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "Point.h"
#include "TetrisBlock.h"
using namespace std;


class Piece {

	vector <Point> blockLocations;
	Point position;
	int rotationStates;
	int currentState;
	Color color;
	
	
	void renderBlock(sf::RenderWindow & window, Point blockLocation);
	void rotate(int direction);
	bool hasBlock(Point location);
	
public:
	Piece();
	~Piece();
	
	
	static const float PIXELS_PER_BLOCK = 20.0f;
	
	/**
	 *	Piece generation methods
	 */
	static Piece square();
	static Piece lblockLeft();
	static Piece lblockRight();
	static Piece stairblockRight();
	static Piece stairblockLeft();
	static Piece longBlock();
	static Piece threeBlock();
	static Piece randomPiece();
	
	vector <TetrisBlock> getGridBlocks();
	
	Point getGridLocation(Point blockLocation);
	
	void rotatePiece();
	void reverseRotate();
	void render(sf::RenderWindow & window);
	void addBlock(Point location);
	void move(Point direction);
	
	vector <Point> getGridLocations();
	
	/**
	 * Accessor Methods
	 */
	Point getPosition() { return position; }
	void setPosition(Point newPosition) { position = newPosition; }
	void setRotationStates(int states) { rotationStates = states; }
	int getRotationStates() { return rotationStates; }
	
};
#endif
