/*
 *  TetrisGrid.h
 *  Tetris
 *
 *  Created by Joshua Belanich.
 */

#ifndef _TETRISGRID_
#define _TETRISGRID_

#include <vector>
#include <map>
#include <SFML/Graphics.hpp>
#include "Point.h"
#include "TetrisPiece.h"
#include "TetrisBlock.h"
using namespace std;

/**
 * TetrisGrid handles the play grid. It keeps track of the blocks that have
 * been inserted in the grid when a piece falls as far as it can. It can
 * check for completed rows and removes them accordingly. Handles collision
 * detection between falling TetrisPieces and the blocks in the grid.
 */
class TetrisGrid {
  vector <TetrisBlock> blocks;
  
public:
  static sf::Image image;
  static sf::Shape background;
  static const int WIDTH = 10;
  static const int HEIGHT = 20;
  static void loadAssets();
	
  int removeFullRows();	
  void addBlocksForPiece(TetrisPiece piece);
  bool hasCollision(TetrisPiece piece);
	
  void render(sf::RenderWindow & window);
};
#endif
