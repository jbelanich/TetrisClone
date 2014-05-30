/*
 *  Point.h
 *  Tetris
 *
 *  Created by Joshua Belanich.
 *
 */

#ifndef _POINT_
#define _POINT_
class Point {
private:
	int x;
	int y;
public:
	Point();
	Point(int x, int y);
	Point(const Point & other);
	~Point();
	
	int getX() const;
	int getY() const;
	void setX(int newX);
	void setY(int newY);
	Point transform(int a, int b, int c, int d);
	bool equals(const Point & other) const;
	Point minus(Point other);
	Point add(Point other);
};
#endif