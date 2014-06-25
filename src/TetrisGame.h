/*
 *  TetrisGame.h
 *  Tetris
 *
 *  Created by Joshua Belanich.
 */

#ifndef _TETRISGAME_
#define _TETRISGAME_
#include "TetrisGrid.h"
#include "TetrisPiece.h"
#include "TetrisScore.h"
#include "TetrisBlock.h"
#include "DisplayBlock.h"
#include <SFML/Graphics.hpp>

/**
 * Main game class. Handles the game loop and key game logic.
 *
 */
class TetrisGame {
  
  //Piece that is currently dropping.
  TetrisPiece currentPiece;

  //Piece that will drop next.
  TetrisPiece nextPiece;
  
  //Game grid.
  TetrisGrid grid;

  //Handles score calculation and rendering.
  TetrisScore scoreBoard;

  //The window
  sf::RenderWindow App;
  
  //how much time until piece drops down a position
  float timePerMove;

  bool running;
	
  void renderNextBlock();
  void rotateIfPossible();
  void moveIfPossible(Point direction);

  void drop();
  void fallAllTheWay();
	
  void testLose();

  void render();
  void renderGameOver();

  void loadAssets();

  //assets
  static DisplayBlock nextPieceSpace;
  sf::Font gameOverFont;
  sf::String gameOverMessage;

  //constants
  static const Point up;
  static const Point down;
  static const Point right;
  static const Point left;
  static const Point startPoint;
	
public:
  void initGame();
  void closeGame();
  int gameLoop();
};
#endif
