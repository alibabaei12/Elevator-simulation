// identification comments code block
// Programmer: Ali Babaei
// Programmer's ID: 1447397

#ifndef Panel_H
#define Panel_H

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Panel
{
  struct Button
  {
    string label;
    bool status;
    int timeStamp;
    static int globalTime;
  };
  friend ostream& operator<<(ostream&, const Button&);
  friend ostream& operator<<(ostream&, const Panel&);

  vector<Button> buttons;

  public:
  void addButton(string);
  void press(string);
  void clear(string);

  bool isLit(string) const ;
  bool areAnyLit() const;

  string getFirstLit() const;
};

#endif
