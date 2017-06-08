// identification comments code block
// Programmer: Ali Babaei
// Programmer's ID: 1447397

#include "Panel.h"
#include "Building.h"

#include <iostream>
using namespace std;

int Panel::Button::globalTime = 0;

void Panel::addButton(string label)
{
  Button b = {label, false};
  buttons.push_back(b);
}

bool Panel::areAnyLit() const
{
  bool found = false;
  for (unsigned int i = 0 ; i < buttons.size(); i++)
    if(buttons[i].status)
    {
      found = true;
      break;
    }
  if (found) return true;
  else return false;
}

void Panel::clear(string label)
{
  int index = -1;
  for (unsigned int i = 0; i < buttons.size(); i++)
  {
    if(buttons[i].label == label)
    {
        index = i;
        break;
    }
  }
  if (index < 0)return;
  buttons[index].status = false;
}

bool Panel::isLit(string label)const
{
   int index = -1;
  for (unsigned int i = 0; i < buttons.size(); i++)
  {
    if (buttons[i].label == label)
    {
        index = i;
        break;
    }
  }
  if (index >= 0)return buttons[index].status;
  return false;
}

void Panel::press(string label)
{
  int index = -1;
  for (unsigned int i = 0; i < buttons.size(); i++)
  {
    if(buttons[i].label == label)
    {
        index = i;
        break;
    }
  }

  if (index < 0) return;
  if(!buttons[index].status)
  {
    buttons[index].status = true;
    buttons[index].timeStamp = Button::globalTime;
    Button::globalTime++;
  }
}

string Panel::getFirstLit() const
{
  int index = -1;
  for (unsigned int i = 0; i < buttons.size(); i++)
    if (buttons[i].status )
      if (index == -1 || buttons[i].timeStamp < buttons[index].timeStamp)
        index = i;
  if(index != -1) return buttons[index].label;
  else return "";
}

ostream& operator<<(ostream& out, const Panel::Button& button)
{
  if(button.status) out<<'['<<button.label << ']';
  return out;
}

ostream& operator<<(ostream& out, const Panel& panel)
{
  for(unsigned int i = 0; i < panel.buttons.size(); i++)
    out<< panel.buttons[i];
  return out;
}

