/*
 *  DisplayBlock.h
 *  Tetris
 *
 *  Created by Joshua Belanich.
 */

#ifndef _DisplayBlock_
#define _DisplayBlock_

#include "Point.h"
#include "Piece.h"
#include <SFML/Graphics.hpp>

class DisplayBlock {
private:
	int width;
	int height;
	Point position;
public:
	
	void setWidth(int newWidth) { width = newWidth; }
	int getWidth() { return width; }
	void setHeight(int newHeight) { height = newHeight; }
	int getHeight() { return height; }
	void setPosition(Point newPosition) { position = newPosition; }
	Point getPosition() { return position; }
	
	void render(sf::RenderWindow & window, Piece piece);
	void render(sf::RenderWindow & window);
	
};

#endif