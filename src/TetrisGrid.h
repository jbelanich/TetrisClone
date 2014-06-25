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
