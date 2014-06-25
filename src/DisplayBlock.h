/*
 *  DisplayBlock.h
 *  Tetris
 *
 *  Created by Joshua Belanich.
 */

#ifndef _DisplayBlock_
#define _DisplayBlock_

#include "Point.h"
#include "TetrisPiece.h"
#include <SFML/Graphics.hpp>

/**
 * This class controls the display that demonstrates the next
 * tetris piece in the sequence.
 */
class DisplayBlock {
  Point position;
  int width;
  int height;

  sf::Shape rectangle();
public:
  
  DisplayBlock(Point pos, int width, int height);

  //rendering
  void render(sf::RenderWindow & window, TetrisPiece piece);
  void render(sf::RenderWindow & window);
	
};

#endif
