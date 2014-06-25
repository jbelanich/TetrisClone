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

class TetrisScore {
  int totalScore;
  int totalLines;
  int level;
  int rowsTowardLevel;
  Point position;

  static const int SCORE_FACTOR = 100;
public:
  TetrisScore();
	
	
  int getTotalScore() { return totalScore; }
  void setTotalScore(int newTotalScore) { totalScore = newTotalScore; }
  Point getPosition() { return position; }
  void setPosition(Point newPosition) { position = newPosition; }
  int getTotalLines() { return totalLines; }
  void setTotalLines(int newTotalLines) { totalLines = newTotalLines; }
	
  void addScoreForRows(int numberOfRows);
	
  void render(sf::RenderWindow & window);
	
  float getTimePerMove();

};
#endif
