/*
 *  TetrisBlock.h
 *  Tetris
 *
 *  Created by Joshua Belanich.
 */

#ifndef _TetrisBlock_
#define _TetrisBlock_

#include <SFML/Graphics.hpp>
#include <map>

#include "Point.h"

using namespace std;

enum Color {
  CYAN, RED, GREEN, YELLOW
};

/**
 * A TetrisBlock is a component of a TetrisPiece. That is,
 * a TetrisPiece is made up of many TetrisBlocks arranged
 * in the proper shape. TetrisBlocks also live on a TetrisGrid
 * when a piece is added to the grid when it falls as far as it
 * can.
 */
class TetrisBlock {	
  //The images corresponding to each colored block.
  static map<Color, sf::Image> colorImages;

  Point position;
  Color color;

public:
  TetrisBlock(Point position, Color color);
  
  //constants
  static const int BLOCK_SIZE = 20;
  static void loadAssets();

  //Render the block to the screen for this App.
  void render(sf::RenderWindow & App);

  //accessors
  void setPosition(Point newPosition) { position = newPosition; }
  Point getPosition() const { return position; }
};
#endif
