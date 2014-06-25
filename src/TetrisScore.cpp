/*
 *  TetrisScore.cpp
 *  Tetris
 *
 *  Created by Joshua Belanich.
 *
 */

#include "TetrisScore.h"

sf::String TetrisScore::scoreDisplay;
sf::Font TetrisScore::scoreFont;
DisplayBlock TetrisScore::displayBlock(Point(11,7), 8, 8);

void TetrisScore::loadAssets() {
  scoreFont.LoadFromFile("images/Arial.ttf");

  scoreDisplay.SetFont(scoreFont);
  scoreDisplay.SetSize(20);
  scoreDisplay.SetPosition(12*20, 8*20);
}


TetrisScore::TetrisScore() 
  : totalScore(0), totalLines(0), level(1), rowsTowardLevel(0), position()
 {}

/**
 *	Renders the Tetris Score at its position.
 */
void TetrisScore::render(sf::RenderWindow & window) {
  stringstream displayData;
  displayData << "Level: " << level;
  displayData << "\n" << "Score: " << totalScore;
  displayData << "\n" << "Lines: " << totalLines;
	
  scoreDisplay.SetText(displayData.str());
	
  displayBlock.render(window);
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
  if(rowsTowardLevel >= ROWS_PER_LEVEL) {
    rowsTowardLevel = 0;
    level++;
  }
}

/**
 *	Returns the time per 1 grid location drop for the Tetris Piece.
 *	This varies with the level.
 */
float TetrisScore::getTimePerMove() {
  return 1.0f / (TIME_FACTOR * level);
}
