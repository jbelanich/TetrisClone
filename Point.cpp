/*
 *  Point.cpp
 *  Tetris
 *
 *  Created by Joshua Belanich
 */

#include "Point.h"

Point::Point(int newX, int newY) {
	x = newX;
	y = newY;
}

Point::Point(const Point & other) {
	x = other.getX();
	y = other.getY();
}

Point::Point() {
	x = 0;
	y = 0;
}

Point::~Point() {

}

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

Point Point::transform(int a, int b, int c, int d) {
	int newX = 0;
	int newY = 0;
	
	newX = (x * a) + (y * b);
	newY = (x * c) + (y * d);
	
	Point retPoint(newX, newY);
	return retPoint;
}

Point Point::minus(Point other) {
	Point returnPoint;
	returnPoint.setX(x - other.getX());
	returnPoint.setY(y - other.getY());
	return returnPoint;
}

Point Point::add(Point other) {
	Point returnPoint;
	returnPoint.setX(x + other.getX());
	returnPoint.setY(y + other.getY());
	return returnPoint;
}

bool Point::equals(const Point & other) const {
	return (other.getX() == x) && (other.getY() == y);
}