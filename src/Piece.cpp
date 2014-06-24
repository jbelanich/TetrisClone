/*
 *  Piece.cpp
 *  Tetris
 *
 *  Created by Joshua Belanich.
 *
 *	This class represents a Tetris Piece that moves and rotates
 *	on a Tetris Grid.
 *
 */

#include "Piece.h"

/**
 *	Generates a square block and returns it.
 */
Piece Piece::square() {
  Piece returnPiece;
  returnPiece.addBlock(Point(1,0));
  returnPiece.addBlock(Point(1,1));
  returnPiece.addBlock(Point(0,1));
  returnPiece.setRotationStates(0);
  return returnPiece;
}

/**
 *	Generates an L-Block that points to the right and returns it.
 */
Piece Piece::lblockRight() {
  Piece returnPiece;
  returnPiece.addBlock(Point(0,-1));
  returnPiece.addBlock(Point(0,1));
  returnPiece.addBlock(Point(1,1));
  returnPiece.setRotationStates(4);
  return returnPiece;
}

/**
 *	Generates an L-Block that points to the left and returns it.
 */
Piece Piece::lblockLeft() {
  Piece returnPiece;
  returnPiece.addBlock(Point(0,-1));
  returnPiece.addBlock(Point(0,1));
  returnPiece.addBlock(Point(-1,1));
  returnPiece.setRotationStates(4);
  return returnPiece;
}

/**
 *	Generates a stair block that points to the right and returns it.
 */
Piece Piece::stairblockRight() {
  Piece returnPiece;
  returnPiece.addBlock(Point(1,0));
  returnPiece.addBlock(Point(-1,1));
  returnPiece.addBlock(Point(0,1));
  returnPiece.setRotationStates(2);
  return returnPiece;
}

/**
 *	Generates a stair block that points to the left and returns it.
 */
Piece Piece::stairblockLeft() {
  Piece returnPiece;
  returnPiece.addBlock(Point(0,1));
  returnPiece.addBlock(Point(1,1));
  returnPiece.addBlock(Point(-1,0));
  returnPiece.setRotationStates(2);
  return returnPiece;
}

/**
 *	Generates a long block and returns it.
 */
Piece Piece::longBlock() {
  Piece returnPiece;
  returnPiece.addBlock(Point(0,-1));
  returnPiece.addBlock(Point(0,-2));
  returnPiece.addBlock(Point(0,1));
  returnPiece.setRotationStates(2);
  returnPiece.rotatePiece();
  return returnPiece;
}

/**
 *	Generates a three block and returns it.
 */
Piece Piece::threeBlock() {
  Piece returnPiece;
  returnPiece.addBlock(Point(0,-1));
  returnPiece.addBlock(Point(1,0));
  returnPiece.addBlock(Point(-1,0));
  returnPiece.setRotationStates(4);
  return returnPiece;
}

/**
 *	Returns a random piece.
 */
Piece Piece::randomPiece() {
  Piece returnPiece;
  int pieceRef = rand() % 7;
  switch (pieceRef) {
  case 0:
    returnPiece = threeBlock();
    break;
  case 1:
    returnPiece = longBlock();
    break;
  case 2:
    returnPiece = stairblockLeft();
    break;
  case 3:
    returnPiece = stairblockRight();
    break;
  case 4:
    returnPiece = lblockLeft();
    break;
  case 5:
    returnPiece = lblockRight();
    break;
  case 6:
    returnPiece = square();
    break;
  default:
    break;
  }
  return returnPiece;
}

Piece::Piece() : currentState(0) {
  color = (Color)(rand()%4);
}

/**
 *	Add a block at the specified location.
 */
void Piece::addBlock(Point location) {
  if(!hasBlockAtLocation(location))
    blockLocations.push_back(location);
}

/**
 *	Rotate the block in a certain direction.
 *	1 - Means rotate clockwise
 *	Any other number means counter-clockwise
 */
void Piece::rotate(int direction) {
  vector <Point> newPositions;
  for(int i = 0; i < blockLocations.size(); i++) {
    if(direction == 1)
      newPositions.push_back(blockLocations[i].rotateClockwise());
    else 
      newPositions.push_back(blockLocations[i].rotateCounterClockwise());
  }

  blockLocations = newPositions;
}

/**
 *	Rotates the piece through its possible rotation states clockwise.  When it reaches
 *	the end of its possible rotation states, the block returns to its original
 *	rotation state.
 */
void Piece::rotatePiece() {
  currentState++;
  if(!(currentState < rotationStates)) {
    currentState = 0;
    for(int i = 0; i < rotationStates-1; i++) {
      rotate(0);
    }
  } else {
    rotate(1);
  }
}

/**
 *	Rotates the piece through its possible rotation states counter-clockwise.
 *	When it reaches the end of its possible rotation states, the block returns
 *	to its original rotation state.
 */
void Piece::reverseRotatePiece() {
  currentState--;
  if((currentState < 0)) {
    currentState = 0;
    for(int i = 0; i < rotationStates-1; i++) {
      rotate(1);
    }
  } else {
    rotate(0);
  }
}

/**
 *	Returns true if the piece has a block at the specified location.
 */
bool Piece::hasBlockAtLocation(Point location) {
  for(int i = 0; i<blockLocations.size(); i++) {
    if(location.equals(blockLocations[i]))
      return true;
  }
  return false;
}

/**
 *	Moves the piece in the specified direction.
 */
void Piece::move(Point direction) {
  position = position.add(direction);
}

/**
 *	Returns the grid locations of the blocks in this piece.
 *	Internally, the block positions are stored relative to
 *	the position of the tetris piece.  This allows for an
 *	easier rotation method.  However, when rendered we need
 *	the position of these blocks on the grid.
 */
vector <Point> Piece::getGridLocations() {
  vector <Point> gridLocations;
  for(int i = 0; i < blockLocations.size(); i++) {
    gridLocations.push_back(getGridLocation(blockLocations[i]));
  }
  gridLocations.push_back(position);
  return gridLocations;
}

/**
 *	Returns the grid location for a specific relative location.
 */
Point Piece::getGridLocation(Point blockLocation) {
  Point temp(blockLocation);
  return temp.add(position);
}

/**
 *	Renders this piece onto the passed RenderWindow.
 *	It renders each block in its specific grid location.
 */
void Piece::render(sf::RenderWindow & window) {
  for(int i = 0; i < blockLocations.size(); i++) {
    renderBlock(window, blockLocations[i]);
  }
  Point point1(0,0);
  renderBlock(window, point1);
}

/**
 *	Renders a block at a specific relative location.
 *	It first converts the passed location into a grid
 *	location.
 */
void Piece::renderBlock(sf::RenderWindow & window, Point blockLocation) {
  TetrisBlock block;
  block.setPosition(getGridLocation(blockLocation));
  block.setColor(color);
  block.render(window);
}

/**
 *	Returns the blocks of this Tetris piece and sets all
 *	of their positions to their grid positions instead of
 *	their relative positions.  This is used for adding the
 *	blocks into the grid.
 */
vector <TetrisBlock> Piece::getGridBlocks() {
  vector <TetrisBlock> returnBlocks;
  for(int i = 0; i < blockLocations.size(); i++) {
    TetrisBlock tempBlock;
    tempBlock.setPosition(getGridLocation(blockLocations[i]));
    tempBlock.setColor(color);
    returnBlocks.push_back(tempBlock);
  }
	
  TetrisBlock centerPiece;
  centerPiece.setPosition(getPosition());
  centerPiece.setColor(color);
  returnBlocks.push_back(centerPiece);
	
  return returnBlocks;
}
