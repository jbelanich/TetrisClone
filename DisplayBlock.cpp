/*
 *  DisplayBlock.cpp
 *  Tetris
 *
 *  Created by Joshua Belanich.
 *
 */

#include "DisplayBlock.h"

/**
 *	Displays this display block at its position with a tetris piece inside centered.
 */
void DisplayBlock::render(sf::RenderWindow & window, Piece piece) {
	sf::Shape rectangle = sf::Shape::Rectangle(position.getX() * TetrisBlock::BLOCK_SIZE,
											   position.getY() * TetrisBlock::BLOCK_SIZE,
											   position.getX() * TetrisBlock::BLOCK_SIZE + width * TetrisBlock::BLOCK_SIZE,
											   position.getY() * TetrisBlock::BLOCK_SIZE + height * TetrisBlock::BLOCK_SIZE,
											   sf::Color(88,83,83));
	Point pos;
	pos.setX(position.getX() + (width/2) - 1);
	pos.setY(position.getY() + (height/2));
	piece.setPosition(pos);
	window.Draw(rectangle);
	piece.render(window);
}

/**
 *	Displays this display block alone at its position.
 */
void DisplayBlock::render(sf::RenderWindow & window) {
	sf::Shape rectangle = sf::Shape::Rectangle(position.getX() * TetrisBlock::BLOCK_SIZE,
											   position.getY() * TetrisBlock::BLOCK_SIZE,
											   position.getX() * TetrisBlock::BLOCK_SIZE + width * TetrisBlock::BLOCK_SIZE,
											   position.getY() * TetrisBlock::BLOCK_SIZE + height * TetrisBlock::BLOCK_SIZE,
											   sf::Color(88,83,83));
	window.Draw(rectangle);
}