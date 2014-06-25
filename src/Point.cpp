/*
 *  Point.cpp
 *  Tetris
 *
 *  Created by Joshua Belanich
 */

#include "Point.h"

/**
 * The parameters a,b,c,d correspond to elements of a 2d integer matrix A where
 * the first row is [a, b] and the second row is [c d]. This method then returns
 * the point Ax, where x is *this.
 */
Point Point::transform(int a, int b, int c, int d) const {
  int newX = (x * a) + (y * b);
  int newY = (x * c) + (y * d);
	
  return Point(newX, newY);
}

/**
 * Apply the matrix [[0, -1],[1, 0]] to this Point to
 * get a clockwise-rotated point.
 */
Point Point::rotateClockwise() const {
  return this->transform(0, -1, 1, 0);
}

/**
 * Apply the matrix [[0, 1],[-1, 0]] to this Point to
 * get a counterclockwise-rotated point.
 */
Point Point::rotateCounterClockwise() const {
  return this->transform(0, 1, -1, 0);
}

Point Point::minus(const Point& other) const {
  Point returnPoint;
  returnPoint.setX(x - other.x);
  returnPoint.setY(y - other.y);
  return returnPoint;
}

Point Point::add(const Point& other) const {
  Point returnPoint;
  returnPoint.setX(x + other.x);
  returnPoint.setY(y + other.y);
  return returnPoint;
}

bool Point::equals(const Point & other) const {
  return (other.x == x) && (other.y == y);
}

Point::Point(int newX, int newY) 
  : x(newX), y(newY) {}

Point::Point() 
  : x(0), y(0) {}

int Point::getX() const {
	return x;
}

int Point::getY() const {
	return y;
}

void Point::setX(int newX) {
	x = newX;
}

void Point::setY(int newY) {
	y = newY;
}

Point Point::zero() {
  return Point(0,0);
}


bool Point::operator==(const Point& other) const {
  return equals(other);
}

bool Point::operator<(const Point& other) const {
  if(x < other.x) {
    return true;
  } else if(x == other.x) {
    return y < other.y;
  } else {
    return false;
  }
}
