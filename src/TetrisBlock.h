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
private:
	Point position;
	Color color;
	int animationState;
public:
	static const int BLOCK_SIZE = 20;
	static map<Color, sf::Image> colorImages;
	static void Init();
	
	void setPosition(Point newPosition) { position = newPosition; }
	void transform(int a, int b, int c, int d) { position = position.transform(a, b, c, d); }
	Point getPosition() { return position; }
	void setColor(Color newColor) { color = newColor; }
	Color getColor() { return color; }
	
	void render(sf::RenderWindow & App);
};
#endif