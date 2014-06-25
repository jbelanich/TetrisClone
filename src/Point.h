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
  int x;
  int y;

public:
  Point();
  Point(int x, int y);

  //accessor methods
  int getX() const;
  int getY() const;
  void setX(int newX);
  void setY(int newY);
  
  //transformation methods
  Point transform(int a, int b, int c, int d) const;
  Point rotateClockwise() const;
  Point rotateCounterClockwise() const;
  Point minus(const Point& other) const;
  Point add(const Point& other) const;

  bool equals(const Point& other) const;

  //some generation methods
  static Point zero();
};
#endif
