// identification comments code block
// Programmer: Ali Babaei
// Programmer's ID: 1447397

#ifndef Rider_H
#define Rider_H

struct Rider
{
  int to;
  int from;
  const bool goingUp;
  const bool goingDown;

  Rider(int , int);
  Rider& operator=(const Rider&);
};

#endif
