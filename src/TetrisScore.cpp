/*
 *  TetrisScore.cpp
 *  Tetris
 *
 *  Created by Joshua Belanich.
 *
 */

#include "TetrisScore.h"


TetrisScore::TetrisScore() 
  : totalScore(0), totalLines(0), level(1), rowsTowardLevel(0), position()
 {}

/**
 *	Renders the Tetris Score at its position.
 */
void TetrisScore::render(sf::RenderWindow & window) {
  DisplayBlock block;
  Point pos(11, 7);
	
  block.setWidth(8);
  block.setHeight(8);
  block.setPosition(pos);
	
  std::stringstream displayData;
  displayData << "Level: " << level;
  displayData << "\n" << "Score: " << totalScore;
  displayData << "\n" << "Lines: " << totalLines;
	
  sf::Font scoreFont;
  scoreFont.LoadFromFile("images/Arial.ttf");

  sf::String scoreDisplay;
  scoreDisplay.SetFont(scoreFont);
  scoreDisplay.SetText(displayData.str());
  scoreDisplay.SetSize(20);
  scoreDisplay.SetPosition(12*20, 8*20);
	
  block.render(window);
  window.Draw(scoreDisplay);
}

/**
 *	Updates the score data for the given number of cleared rows.
 *	This may update the level, the score, or the number of
 *	cleared rows.
 */
void TetrisScore::addScoreForRows(int numberOfRows) {
  totalScore += (numberOfRows * numberOfRows * SCORE_FACTOR);
  totalLines += numberOfRows;
  rowsTowardLevel += numberOfRows;
  if(rowsTowardLevel >= 10) {
    rowsTowardLevel = 0;
    level++;
  }
}

/**
 *	Returns the time per 1 grid location drop for the Tetris Piece.
 *	This varies with the level.
 */
float TetrisScore::getTimePerMove() {
  float startTime = 1.0f;
  for(int i = 0; i < level; i++) {
    startTime /= 1.50f;
  }
  return startTime;
}
