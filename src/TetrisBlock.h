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

class TetrisBlock {	
  //The images corresponding to each colored block.
  static map<Color, sf::Image> colorImages;

  Point position;
  Color color;

public:
  static const int BLOCK_SIZE = 20;
  static void loadAssets();

  //Render the block to the screen for this App.
  void render(sf::RenderWindow & App);
  
  void setPosition(Point newPosition) { position = newPosition; }
  Point getPosition() { return position; }
  void setColor(Color newColor) { color = newColor; }
  Color getColor() { return color; }
};
#endif
