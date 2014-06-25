/*
 *  TetrisGame.cpp
 *  Tetris
 *
 *  Created by Joshua Belanich.
 *
 */

#include "TetrisGame.h"

DisplayBlock TetrisGame::nextPieceSpace(Point(TetrisGrid::WIDTH + 1, 0), 8, 5);

//constants
const Point TetrisGame::startPoint(5,0);
const Point TetrisGame::up(0,-1);
const Point TetrisGame::down(0,1);
const Point TetrisGame::right(1,0);
const Point TetrisGame::left(-1,0);

void TetrisGame::loadAssets() {
  if(!gameOverFont.LoadFromFile("images/Arial.ttf", 50))
    std::cout << "Error Loading Font";

  gameOverMessage = sf::String("Game Over!", gameOverFont, 30);

  gameOverMessage.Move(TetrisGrid::WIDTH/2, TetrisGrid::HEIGHT/2);
}

/**
 * Initializes the game by loading the appropriate
 * images and Tetris Pieces.
 */
void TetrisGame::initGame() {
  App.Create(sf::VideoMode(380,400), "SFML Graphics");

  srand(time(NULL));

  TetrisGame::loadAssets();	
  TetrisGrid::loadAssets();
  TetrisBlock::loadAssets();
  TetrisScore::loadAssets();

  currentPiece = TetrisPiece::randomPiece();
  currentPiece.setPosition(startPoint);
  nextPiece = TetrisPiece::randomPiece();
  nextPiece.setPosition(startPoint);
	
  running = true;
	
  scoreBoard.setPosition(Point(400,400));
}

/**
 * Closes the game.  Displays a Game Over Message
 * onto the screen and the score.  Waits for the user
 * to exit the game.
 */
void TetrisGame::closeGame() {
  while(App.IsOpened()) {
    sf::Event Event; 
		
    while (App.GetEvent(Event)) {
      if (Event.Type == sf::Event::Closed)
	App.Close();
    }
    
    renderGameOver();
  }
	
}

/**
 * Rotates the Tetris Piece if possible.  A Tetris Piece
 * cannot rotate if it will result in a collision while
 * doing so.
 */
void TetrisGame::rotateIfPossible() {
  currentPiece.rotatePiece();
  if(grid.hasCollision(currentPiece))
    currentPiece.reverseRotatePiece();
}

/**
 * Moves the Tetris Piece in the given direciton if possible.  A Tetris Piece
 * cannot move if moving it will result in a collision.
 */
void TetrisGame::moveIfPossible(Point direction) {
  currentPiece.move(direction);
  if(grid.hasCollision(currentPiece)) {
    currentPiece.move(direction.negate());
  }
}

/**
 * Drops the Tetris Piece by one grid location.  After
 * dropping down, the method checks if there is a collision.  If so,
 * it will destroy this piece and add its blocks onto the grid.  It
 * will also check if there are any full rows, and will start a new
 * dropping piece.
 */
void TetrisGame::drop() {
  currentPiece.move(down);
	
  //we have a collision, move piece back up one and
  //add the piece's blocks to the grid.
  if(grid.hasCollision(currentPiece)) {
    currentPiece.move(up);
		
    grid.addBlocksForPiece(currentPiece);
		
    currentPiece = nextPiece;
    currentPiece.setPosition(startPoint);
		
    nextPiece = TetrisPiece::randomPiece();
    nextPiece.setPosition(startPoint);
	
    scoreBoard.addScoreForRows(grid.removeFullRows());

    testLose();
  }
}

/**
 * Causes the block to drop down to the lowest possible
 * position.
 */
void TetrisGame::fallAllTheWay() {
  while(!grid.hasCollision(currentPiece)) {
    currentPiece.move(down);
  }
	
  currentPiece.move(up);
  drop();
}

/**
 * Test is the user has lost.  This happens when
 * a block spawns and it immediately has a collision.
 */
void TetrisGame::testLose() {
  if(grid.hasCollision(currentPiece)) {
    running = false;
  }
}

/**
 * Displays the next block to the right of the Tetris Grid.
 */
void TetrisGame::renderNextBlock() {
  nextPieceSpace.render(App, nextPiece);
}

/**
 * The game loop.  It waits for user interaction in moving the
 * block.  At a given time interval, the game will drop the 
 * Tetris Piece down.  This gets faseter as move rows are cleared.
 */
int TetrisGame::gameLoop() {
  float timeElapsed = 0.0f;
  float timeCounter = 0.0f;
	
  while (running && App.IsOpened()) {
    timeElapsed = App.GetFrameTime();
    timeCounter += timeElapsed;
			
    sf::Event Event;

    while (App.GetEvent(Event)) {
      if (Event.Type == sf::Event::Closed)
	App.Close();

      //move block
      if((Event.Type == sf::Event::KeyPressed)) {
	if(Event.Key.Code == sf::Key::Up)
	  rotateIfPossible();
	if(Event.Key.Code == sf::Key::Right)
	  moveIfPossible(right);
	if(Event.Key.Code == sf::Key::Left)
	  moveIfPossible(left);
	if(Event.Key.Code == sf::Key::Down)
	  drop();
	if(Event.Key.Code == sf::Key::Space)
	  fallAllTheWay();
      }
    }
	       
    //reset time counter if necessary
    if(timeCounter > scoreBoard.getTimePerMove()) {
      timeCounter = 0.0f;
      drop();
    }
			
    render();
  }
		
  return EXIT_SUCCESS;
}

void TetrisGame::render() {
  App.Clear();
  
  renderNextBlock();
  grid.render(App);
  currentPiece.render(App);
  scoreBoard.render(App);
  
  App.Display();
}

void TetrisGame::renderGameOver() {
 App.Clear();
			
 grid.render(App);
 currentPiece.render(App);
 App.Draw(gameOverMessage);
 scoreBoard.render(App);
			
 App.Display();  
}

