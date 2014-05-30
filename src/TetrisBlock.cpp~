/*
 *  TetrisBlock.cpp
 *  Tetris
 *
 *  Created by Joshua Belanich.
 *
 */

#include "TetrisBlock.h"


map<Color, sf::Image> TetrisBlock::colorImages;

/**
 *	Loads all of the images for the possible block colors.
 */
void TetrisBlock::Init() {
	colorImages[CYAN].LoadFromFile("cyan.png");
	colorImages[RED].LoadFromFile("red.png");
	colorImages[GREEN].LoadFromFile("green.png");
	colorImages[YELLOW].LoadFromFile("yellow.png");
}

/**
 *	Renders the block onto the window at the position of
 *	the block.
 */
void TetrisBlock::render(sf::RenderWindow & window) {
	sf::Sprite blockSprite;
	blockSprite.SetImage(colorImages[color]);
	blockSprite.Resize(20.0f,20.0f);
	blockSprite.SetScale(1.0f,1.0f);
	blockSprite.SetPosition(position.getX()*BLOCK_SIZE, position.getY()*BLOCK_SIZE);
	window.Draw(blockSprite);
}