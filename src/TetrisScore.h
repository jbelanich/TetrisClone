/*
 *  TetrisScore.h
 *  Tetris
 *
 *  Created by Joshua Belanich.
 */

#ifndef _TETRISSCORE_
#define _TETRISSCORE_

#include <SFML/Graphics.hpp>
#include <sstream>
#include "Point.h"
#include "DisplayBlock.h"

using namespace std;

class TetrisScore {
  int totalScore;
  int totalLines;
  int level;

  //rows we have cleared in this level
  int rowsTowardLevel;
  
  //where to render the score
  Point position;

  //assets
  static sf::String scoreDisplay;
  static sf::Font scoreFont;
  static DisplayBlock displayBlock;

  //constants
  static const int SCORE_FACTOR = 100;
  static const int ROWS_PER_LEVEL = 10;
  static const float TIME_FACTOR = 1.5f;
public:
  TetrisScore();

  static void loadAssets();

  //accessors
  Point getPosition() { return position; }
  void setPosition(Point pos) { position = pos; }

  //interactions with TetrisGame
  void addScoreForRows(int numberOfRows);
  float getTimePerMove();
	
  //rendering
  void render(sf::RenderWindow & window);	

};
#endif
