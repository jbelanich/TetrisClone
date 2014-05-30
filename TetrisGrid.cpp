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

/**
 *	Adds a block onto the grid.
 */
void TetrisGrid::addBlock(TetrisBlock block) {
	if(inBounds(block.getPosition()))
		blocks.push_back(block);
}

/**
 *	Checks if the TetrisGrid has a block at the
 *	specified location.
 */
bool TetrisGrid::hasBlock(Point location) {
	for(int i = 0; i<blocks.size(); i++) {
		if(location.equals(blocks[i].getPosition()))
			return true;
	}
	return false;
}

/**
 *	Checks if the piece is colliding with anything on
 *	the grid.  A collision occurs if the piece is out of
 *	bounds or if it is overlapping with any of the other
 *	blocks in the grid.
 */
bool TetrisGrid::hasCollision(Piece piece) {
	vector <Point> pieceGridLocations = piece.getGridLocations();
	for(int i = 0; i < pieceGridLocations.size(); i++) {
		Point temp = pieceGridLocations[i];
		if(hasBlock(temp) || !inBounds(temp))
			return true;
	}
	return false;
}

/**
 *	Returns true is the given point is in the boundaries
 *	of the Tetris Grid.
 */
bool TetrisGrid::inBounds(Point point) {
	return ((point.getX() < WIDTH) 
			&& (point.getY() < HEIGHT) 
			&& (point.getX() >= 0));
}

/**
 *	Adds all of the blocks from the given piece
 *	into the grid.
 */
void TetrisGrid::addBlocks(Piece piece) {
	vector <TetrisBlock> gridBlocks = piece.getGridBlocks();
	for(int i = 0; i < gridBlocks.size(); i++) {
		addBlock(gridBlocks[i]);
	}
	//put the center block in the getGridBlocks() function
}

/**
 *	Renders a single block from the grid onto the screen.
 */
void TetrisGrid::renderBlock(sf::RenderWindow & window, TetrisBlock block) {
	block.render(window);
}

/**
 *	Renders the background of the grid onto the screen.
 */
void TetrisGrid::renderBackground(sf::RenderWindow & window) {
	sf::Shape rect = sf::Shape::Rectangle(0.0f, 0.0f, (float)WIDTH * TetrisBlock::BLOCK_SIZE,
										  (float)HEIGHT * TetrisBlock::BLOCK_SIZE, 
										  sf::Color(88,83,83), 0.0f, 
										  sf::Color(88,83,83));
	window.Draw(rect);
}

/**
 *	Renders the whole grid onto the screen.  It first renders
 *	the background then renders each individual block.
 */
void TetrisGrid::render(sf::RenderWindow & window) {
	renderBackground(window);
	for(int i = 0; i < blocks.size(); i++) {
		renderBlock(window, blocks[i]);
	}
}

/**
 *	Removes the full rows from the Tetris Grid.  This method
 *	then returns how many rows were removed.  After removing
 *	the rows it then drops down all the rows above the removed
 *	rows down.
 */
int TetrisGrid::removeFullRows() {
	int numberOfRowsRemoved = 0;
	map <int, int> rowCounts;
	map <int, int> dropDownCounts;
	for(int i = 0; i < blocks.size(); i++) {
		rowCounts[blocks[i].getPosition().getY()]++;
	}
	
	for(map<int,int>::reverse_iterator mIter = rowCounts.rbegin(); mIter != rowCounts.rend(); mIter++) {
		if(mIter->second == WIDTH) {
			numberOfRowsRemoved++;
			for(int i = 0; i < mIter->first; i++) {
				dropDownCounts[i]++;
			}
		}
	}
	
	vector<TetrisBlock>::iterator iter = blocks.begin();
	while(iter != blocks.end()) {
		if(rowCounts[iter->getPosition().getY()] == WIDTH) {
			iter = blocks.erase(iter);
		} else {
			Point position(iter->getPosition().getX(), iter->getPosition().getY()
						   + dropDownCounts[iter->getPosition().getY()]);
			iter->setPosition(position);
			iter++;
		}
	}
	
	return numberOfRowsRemoved;
}