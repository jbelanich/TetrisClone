/*
 *  TetrisGame.cpp
 *  Tetris
 *
 *  Created by Joshua Belanich.
 *
 */

#include "TetrisGame.h"

/**
 *	Initializes the game by loading the appropriate
 *	images and Tetris Pieces.
 */
void TetrisGame::initGame() {
	srand(time(NULL));
	
	TetrisGrid::loadAssets();
	TetrisBlock::loadAssets();
	
	Point startPoint(5,0);
	currentPiece = Piece::randomPiece();
	currentPiece.setPosition(startPoint);
	nextPiece = Piece::randomPiece();
	nextPiece.setPosition(startPoint);
	
	running = true;
	
	Point boardPosition(400,400);
	scoreBoard.setPosition(boardPosition);
}

/**
 *	Closes the game.  Displays a Game Over Message
 *	onto the screen and the score.  Waits for the user
 *	to exit the game.
 */
void TetrisGame::closeGame() {
	sf::Font GameOverFont;
	if(!GameOverFont.LoadFromFile("images/Arial.ttf", 50))
		std::cout << "Error Loading Font";
	sf::String GameOverMessage("Game Over!", GameOverFont, 30);
	GameOverMessage.Move(TetrisGrid::WIDTH/2, TetrisGrid::HEIGHT/2);
	
	while(App.IsOpened()) {
		sf::Event Event; 
		
		while (App.GetEvent(Event))
		{
		
			if (Event.Type == sf::Event::Closed)
				App.Close();
		}
			
		App.Clear();
			
		grid.render(App);
		currentPiece.render(App);
		App.Draw(GameOverMessage);
		scoreBoard.render(App);
			
		App.Display();
	}
	
}

/**
 *	Rotates the Tetris Piece if possible.  A Tetris Piece
 *	cannot rotate if it will result in a collision while
 *	doing so.
 */
void TetrisGame::rotateIfPossible() {
	currentPiece.rotatePiece();
	if(grid.hasCollision(currentPiece))
		currentPiece.reverseRotatePiece();
}

/**
 *	Moves the Tetris Piece in the given direciton if possible.  A Tetris Piece
 *	cannot move if moving it will result in a collision.
 */
void TetrisGame::moveIfPossible(Point direction) {
	currentPiece.move(direction);
	if(grid.hasCollision(currentPiece)) {
		currentPiece.setPosition(currentPiece.getPosition().minus(direction));
	}
}

/**
 *	This method drops the Tetris Piece by one grid location.  After
 *	dropping down, the method checks if there is a collision.  If so,
 *	it will destroy this piece and add its blocks onto the grid.  It
 *	will also check if there are any full rows, and will start a new
 *	dropping piece.
 */
void TetrisGame::drop() {
	Point down(0,1);
	
	currentPiece.move(down);
	
	if(grid.hasCollision(currentPiece)) {
		currentPiece.setPosition(currentPiece.getPosition().minus(down));
		
		Point startPosition(5,0);
		
		grid.addBlocks(currentPiece);
		
		currentPiece = nextPiece;
		currentPiece.setPosition(startPosition);
		
		nextPiece = Piece::randomPiece();
		nextPiece.setPosition(startPosition);
		
		scoreBoard.addScoreForRows(grid.removeFullRows());
		testLose();
	}
}

/**
 *	Causes the block to drop down to the lowest possible
 *	position.
 */
void TetrisGame::fallAllTheWay() {
	Point down(0,1);
	Point up(0,-1);
	
	while(!grid.hasCollision(currentPiece)) {
		currentPiece.move(down);
	}
	
	currentPiece.move(up);
	drop();
}

/**
 *	Test is the user has lost.  This happens when
 *	a block spawns and it immediately has a collision.
 */
void TetrisGame::testLose() {
	if(grid.hasCollision(currentPiece)) {
		running = false;
	}
}

/**
 *	Displays the next block to the right of the Tetris Grid.
 */
void TetrisGame::displayNextBlock() {
	Point displayPosition(TetrisGrid::WIDTH + 1, 0);
	DisplayBlock nextPieceSpace;
	nextPieceSpace.setWidth(8);
	nextPieceSpace.setHeight(5);
	nextPieceSpace.setPosition(displayPosition);
	nextPieceSpace.render(App, nextPiece);
}

/**
 *	The game loop.  It waits for user interaction in moving the
 *	block.  At a given time interval, the game will drop the 
 *	Tetris Piece down.  This gets faseter as move rows are cleared.
 */
int TetrisGame::gameLoop() {

	App.Create(sf::VideoMode(380,400), "SFML Graphics");
	
	initGame(); 
	float timeElapsed = 0.0f;
	float timeCounter = 0.0f;
	
	Point right(1,0);
	Point down(0,1);
	Point up(0,-1);
	Point left(-1,0);
		
		
		while (running && App.IsOpened())
		{
			timeElapsed = App.GetFrameTime();
			timeCounter += timeElapsed;
			
			sf::Event Event;

			while (App.GetEvent(Event))
			{
				if (Event.Type == sf::Event::Closed)
					App.Close();
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
			
			if(timeCounter > scoreBoard.getTimePerMove()) {
				timeCounter = 0.0f;
				drop();
			}
			
			App.Clear();
			
			displayNextBlock();
			grid.render(App);
			currentPiece.render(App);
			scoreBoard.render(App);
			
			App.Display();
		}
		
		return EXIT_SUCCESS;
}

