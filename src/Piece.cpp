/*
 *  Piece.cpp
 *  Tetris
 *
 *  Created by Joshua Belanich.
 */

#include "Piece.h"

Piece::Piece() : currentState(0) {
  color = (Color)(rand()%4);
}

/**
 * Generates a square block and returns it.
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
 * Generates an L-Block that points to the right and returns it.
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
 * Generates an L-Block that points to the left and returns it.
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
 * Generates a stair block that points to the right and returns it.
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
 * Generates a stair block that points to the left and returns it.
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
 * Generates a long block and returns it.
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
 * Generates a three block and returns it.
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
 * Returns a random piece.
 */
Piece Piece::randomPiece() {
  int pieceRef = rand() % 7;
  switch (pieceRef) {
  case 0:
    return threeBlock();
    break;
  case 1:
    return longBlock();
    break;
  case 2:
    return stairblockLeft();
    break;
  case 3:
    return stairblockRight();
    break;
  case 4:
    return lblockLeft();
    break;
  case 5:
    return lblockRight();
    break;
  case 6:
    return square();
    break;
  default:
    return longBlock();
  }
}

/**
 * Add a block at the specified location. Used for constructing
 * the block shapes.
 */
void Piece::addBlock(Point location) {
  if(!hasBlockAtLocation(location))
    blockLocations.push_back(location);
}

/**
 * Rotate the piece in the provided direction.
 */
void Piece::rotate(Direction direction) {
  vector<Point> newPositions;
  vector<Point>::iterator iter;
  for(iter = blockLocations.begin(); iter != blockLocations.end(); ++iter) {
    if(direction == CLOCKWISE)
      newPositions.push_back(iter->rotateClockwise());
    else 
      newPositions.push_back(iter->rotateCounterClockwise());
  }

  blockLocations = newPositions;
}

/**
 *	Rotates the piece through its possible rotation states clockwise.  When it reaches
 *	the end of its possible rotation states, the piece returns to its original
 *	rotation state.
 */
void Piece::rotatePiece() {
  currentState++;
  if(currentState >= rotationStates) {
    currentState = 0;

    //rotate all the way back to original position.
    for(int i = 0; i < rotationStates-1; i++) {
      rotate(COUNTER_CLOCKWISE);
    }
  } else {
    //just rotate normally
    rotate(CLOCKWISE);
  }
}

/**
 *	Rotates the piece through its possible rotation states counter-clockwise.
 *	When it reaches the end of its possible rotation states, the block returns
 *	to its original rotation state.
 */
void Piece::reverseRotatePiece() {
  currentState--;
  if(currentState < 0) {
    currentState = 0;

    //rotate all the way to original position.
    for(int i = 0; i < rotationStates-1; i++) {
      rotate(CLOCKWISE);
    }
  } else {
    //just rotate normally
    rotate(COUNTER_CLOCKWISE);
  }
}

/**
 * Returns true if the piece has a block at the specified location.
 */
bool Piece::hasBlockAtLocation(Point location) {
  for(int i = 0; i<blockLocations.size(); i++) {
    if(location.equals(blockLocations[i]))
      return true;
  }
  return false;
}

/**
 * Checks if we have a collision with the provided list of blocks.
 */
bool Piece::hasCollisionWithBlocks(const vector<TetrisBlock>& blocks) {
  vector<TetrisBlock>::const_iterator blockIter;
  for(blockIter = blocks.begin(); blockIter != blocks.end(); ++blockIter) {
    //check collision with internal grid locations
    vector<Point>::iterator blockLocationIter;
    for(blockLocationIter = blockLocations.begin(); blockLocationIter != blockLocations.end(); ++blockLocationIter) {
      if(getGridLocation(*blockLocationIter) == blockIter->getPosition()) {
	return true;
      }
    }

    //check our implicit block
    if(position == blockIter->getPosition()) {
      return true;
    }
  }

  return false;
}

/**
 * Adds our internal blocks to the provided list of blocks.
 */
void Piece::addSelfToBlocks(vector<TetrisBlock>& blocks) {
  vector<Point>::iterator locationIter;
  for(locationIter = blockLocations.begin(); locationIter != blockLocations.end(); ++locationIter) {
    TetrisBlock tempBlock;
    tempBlock.setPosition(getGridLocation(*locationIter));
    tempBlock.setColor(color);
    blocks.push_back(tempBlock);
  }
	
  //add implicit center piece.
  TetrisBlock centerPiece;
  centerPiece.setPosition(position);
  centerPiece.setColor(color);
  blocks.push_back(centerPiece);
}

/**
 * Checks if the piece is within the provided bounds.
 */
bool Piece::inBounds(int width, int height) {
  vector<Point>::iterator locationIter;
  for(locationIter = blockLocations.begin(); locationIter != blockLocations.end(); ++locationIter) {
    Point gridLocation = getGridLocation(*locationIter);
    if(!inBounds(gridLocation, width, height)) {
      return false;
    }
  }
  
  //check implicit point
  return inBounds(position, width, height);
}

/**
 * Checks if provided point is within the provided bounds.
 */
bool Piece::inBounds(Point p, int width, int height) {
  return (p.getX() < width) && (p.getY() < height)
    && (p.getX() >= 0);
}

/**
 * Moves the piece in the specified direction.
 */
void Piece::move(Point direction) {
  position = position.add(direction);
}

/**
 * Returns the grid location for a specific relative location.
 */
Point Piece::getGridLocation(Point blockLocation) {
  return blockLocation.add(position);
}

/**
 * Renders this piece onto the passed RenderWindow.
 * It renders each block in its specific grid location.
 */
void Piece::render(sf::RenderWindow & window) {
  for(int i = 0; i < blockLocations.size(); i++) {
    renderBlock(window, blockLocations[i]);
  }

  //render implicit block
  renderBlock(window, Point::zero());
}

/**
 * Renders a block at a specific relative location.
 * It first converts the passed location into a grid
 * location.
 */
void Piece::renderBlock(sf::RenderWindow& window, Point blockLocation) {
  TetrisBlock block;
  block.setPosition(getGridLocation(blockLocation));
  block.setColor(color);
  block.render(window);
}
