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

enum Direction {
  CLOCKWISE,COUNTER_CLOCKWISE
};

/**
 * A TetrisPiece is a collection of TetrisBlocks arranged in the appropriate pattern. Internally,
 * this is represented by a vector of Positions indicating where the relevant blocks are located.
 * When we need to add the piece to the TetrisGrid, we turn this list of positions into a list
 * of TetrisBlocks of the proper color.
 * 
 * Note that for every TetrisPiece there is an *implicit block* at point (0,0).
 */

class Piece {

  //Location of the blocks that make up this piece. Locations
  //are *relative* to the position of the piece.
  vector <Point> blockLocations;

  //Position of piece
  Point position;

  //The number of rotation states this piece has. For example, a square has 0 because
  //of its symmetry, and a l-block has 4, because of its asymmetry.
  int rotationStates;

  //Current rotation state of this piece.
  int currentState;

  //Whole piece color.
  Color color;

  //Internal utilities
  void renderBlock(sf::RenderWindow & window, Point blockLocation);
  void rotate(Direction direction);
  bool hasBlockAtLocation(Point location);
  Point getGridLocation(Point blockLocation);
  void addBlock(Point location);
  bool inBounds(Point p, int width, int height);
	
public:
  Piece();
	
  //Piece generation methods
  static Piece square();
  static Piece lblockLeft();
  static Piece lblockRight();
  static Piece stairblockRight();
  static Piece stairblockLeft();
  static Piece longBlock();
  static Piece threeBlock();
  static Piece randomPiece();
  
  //transformations
  void rotatePiece();
  void reverseRotatePiece();
  void move(Point direction);

  //interaction with grid
  bool inBounds(int width, int height);
  void addSelfToBlocks(vector<TetrisBlock>& blocks);
  bool hasCollisionWithBlocks(const vector<TetrisBlock>& blocks);

  //rendering
  void render(sf::RenderWindow & window);
	
  //accessor methods
  Point getPosition() { return position; }
  void setPosition(Point newPosition) { position = newPosition; }
  void setRotationStates(int states) { rotationStates = states; }
  int getRotationStates() { return rotationStates; }
	
};
#endif
