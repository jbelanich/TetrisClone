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

/**
 * This class controls the display that demonstrates the next
 * tetris piece in the sequence.
 */
class DisplayBlock {
private:
  int width;
  int height;
  Point position;

  static sf::Shape rectangle;
public:

  void loadAssets();
	
  //accessors
  void setWidth(int newWidth) { width = newWidth; }
  int getWidth() { return width; }
  void setHeight(int newHeight) { height = newHeight; }
  int getHeight() { return height; }
  void setPosition(Point newPosition) { position = newPosition; }
  Point getPosition() { return position; }
	
  //rendering
  void render(sf::RenderWindow & window, Piece piece);
  void render(sf::RenderWindow & window);
	
};

#endif
