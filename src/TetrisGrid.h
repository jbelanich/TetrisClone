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
#include "Piece.h"
#include "TetrisBlock.h"
using namespace std;

class TetrisGrid {
private:
	vector <TetrisBlock> blocks;
	
	void renderBlock(sf::RenderWindow & window, TetrisBlock block);
	void renderBackground(sf::RenderWindow & window);
	
	bool hasBlock(Point location);
	void addBlock(TetrisBlock block);
	bool inBounds(Point point);
public:
	static sf::Image image;
	static const int WIDTH = 10;
	static const int HEIGHT = 20;
	
	static void Init() {
		image.LoadFromFile("images/gridImage.png");
	}
	
	int removeFullRows();
	
	void addBlocks(Piece piece);
	
	bool hasCollision(Piece piece);
	
	void render(sf::RenderWindow & window);
};
#endif
