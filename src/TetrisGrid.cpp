/*
 *  TetrisGrid.cpp
 *  Tetris
 *
 *  Created by Joshua Belanich.
 *  
 *
 */

#include "TetrisGrid.h"

sf::Image TetrisGrid::image;
sf::Shape TetrisGrid::background;

void TetrisGrid::loadAssets() {
  image.LoadFromFile("images/gridImage.png");

  background = sf::Shape::Rectangle(0.0f, 0.0f, (float)WIDTH * TetrisBlock::BLOCK_SIZE,
					(float)HEIGHT * TetrisBlock::BLOCK_SIZE, 
					sf::Color(88,83,83), 0.0f, 
					sf::Color(88,83,83));
}

/**
 * Checks if the piece is colliding with anything on
 * the grid.  A collision occurs if the piece is out of
 * bounds or if it is overlapping with any of the other
 * blocks in the grid.
 */
bool TetrisGrid::hasCollision(Piece piece) {
  return piece.hasCollisionWithBlocks(blocks) || !piece.inBounds(WIDTH,HEIGHT);
}

/**
 * Adds all of the blocks from the given piece
 * into the grid.
 */
void TetrisGrid::addBlocksForPiece(Piece piece) {
  piece.addSelfToBlocks(blocks);
}

/**
 * Renders the whole grid onto the screen.  It first renders
 * the background then renders each individual block.
 */
void TetrisGrid::render(sf::RenderWindow & window) {
  window.Draw(background);
  
  //draw blocks
  vector<TetrisBlock>::iterator iter;
  for(iter = blocks.begin(); iter != blocks.end(); ++iter) {
    iter->render(window);
  }
}

/**
 * Removes the full rows from the Tetris Grid.  This method
 * then returns how many rows were removed.  After removing
 * the rows it then drops down all the rows above the removed
 * rows.
 */
int TetrisGrid::removeFullRows() {
  //will return this value
  int numberOfRowsRemoved = 0;

  //mapping between row -> number of blocks in row
  map <int, int> rowCounts;

  //mapping between row -> how many rows down it will drop.
  map <int, int> dropDownCounts;

  //find out how many blocks are in each row
  vector<TetrisBlock>::iterator blockIter;
  for(blockIter = blocks.begin(); blockIter != blocks.end(); ++blockIter) {
    rowCounts[blockIter->getPosition().getY()]++;
  }
	
  //figure out how many rows need to be removed, and calculate
  //drop counts.
  map<int,int>::reverse_iterator rIter;
  for(rIter = rowCounts.rbegin(); rIter != rowCounts.rend(); ++rIter) {
    //if all slots in the row are filled...
    if(rIter->second == WIDTH) {
      numberOfRowsRemoved++;
      
      //all rows above this row will need to be
      //dropped down by 1 because we are going
      //to erase this row.
      for(int i = 0; i < rIter->first; i++) {
	dropDownCounts[i]++;
      }
    }
  }
	
  //commit the changes to the grid. Remove the correct rows,
  //and drop the appropriate blocks.
  for(blockIter = blocks.begin(); blockIter != blocks.end(); ) {
    //if the block is in a row that is going to be deleted...
    if(rowCounts[blockIter->getPosition().getY()] == WIDTH) {
      //delete the block
      blockIter = blocks.erase(blockIter);
    } else {
      //Since we are not deleting this block, we will drop it down
      //by the number of rows deleted below it.
      Point currentPosition = blockIter->getPosition();
      int newX = currentPosition.getX();
      int newY = currentPosition.getY() + dropDownCounts[currentPosition.getY()];

      blockIter->setPosition(Point(newX,newY));
      ++blockIter;
    }
  }
	
  return numberOfRowsRemoved;
}
