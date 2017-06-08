// identification comments code block
// Programmer: Ali Babaei
// Programmer's ID: 1447397

#include "Elevator.h"
#include "Panel.h"
#include "Building.h"

#include <iostream>
#include <vector>

using namespace std;

#include <cstdlib>

Elevator::Elevator(unsigned int capacity, int speed, int start)
:speed(speed), CAPACITY(capacity), direction(IDLE), timer(0), atFloorIndex(-1)
{
  for (int i = 0; i < Building::FLOORS; i++)
  panel.addButton(Building::floors[i].label);

  location = Building::floors[start];
}

ostream& operator<<(ostream& out, const Elevator& e)
{
  out << "Elevator at";
  out.width(6);
  out << e.location;

  out.width(13);
  if(e.direction == e.UP){
    out << " going UP ";
  }
  else if(e.direction == e.DOWN){
    out << " going DOWN ";
  }
  else{
    out << " idle ";
  }

  out.width(4);
  out << e.riders.size() << " " << "riders";

  if (e.atFloorIndex != -1)
    out << " door is OPEN|" << e.timer << " ";

  out << e.panel;
  return out;
}

void Elevator::openDoorTo(int index)
{
  panel.clear(Building::floors[index].label);
  atFloorIndex = index;
  resetTimer();
}

void Elevator::board(const Rider& r)
{
  riders.push_back(r);
  panel.press(Building::floors[r.to].label);
  if(r.goingUp)direction = UP;
  else if(r.goingDown)direction = DOWN;
    else cout << "error 2";
  resetTimer();
}

bool Elevator::hasRiderForFloor() const
{
  if (!isOpen())
    return false;

  for (unsigned int i = 0 ; i < riders.size(); i++)
  {
    if(riders[i].to == atFloorIndex)
    {
      return true;
    }
  }
  return false;
}

void Elevator::removeRider()
{
  for (int i = 0 ; i < riders.size(); i++)
  {
    if(riders[i].to == atFloorIndex)
    {
      riders.erase(riders.begin() + i);

      //clear the host elevator's panel button for the elevator's current floor
      panel.clear(Building::floors[riders[i].to].label);

      // reset the host elevator's count-down timer
      resetTimer();
      break;
    }
  }
}

bool Elevator::closeDoor()
{
  if(atFloorIndex == -1){
    return false;
  }
  else{
    if(goingUp() && !Building::floors[atFloorIndex].hasUpRider()){
      Building::floors[atFloorIndex].panel.clear(Building::floors[atFloorIndex].UP);
    }
    if(goingDown() && !Building::floors[atFloorIndex].hasDownRider()){
      Building::floors[atFloorIndex].panel.clear(Building::floors[atFloorIndex].DOWN);
    }
    atFloorIndex = -1;
  }
  return true;
}

bool Elevator::move()
{
  if (goingUp())
  {
    for (int i = 0; i < Building::FLOORS; i++)
    {
      if (Building::floors[i].elevation < location ||  ((Building::floors[i].elevation - location) > speed))continue;

      else if (Building::floors[i].panel.isLit(Floor::UP) || panel.isLit(Building::floors[i].label))
      {
        if (location != Building::floors[i].elevation)
        {
          location = Building::floors[i].elevation;
          openDoorTo(i);
          return true;
        }
      }
    }

    if (Floor::TOP - location < speed)return false;
    else {
      location += speed;
      return true;
    }
  }

  else if (goingDown())
  {
    for (int i = 0; i < Building::FLOORS; i++)
    {
      if (Building::floors[i].elevation > location || ((location - Building::floors[i].elevation) > speed)) continue;

      else if (Building::floors[i].panel.isLit(Floor::DOWN) || panel.isLit(Building::floors[i].label))
      {
        if (location != Building::floors[i].elevation)
        {
          location = Building::floors[i].elevation;
          openDoorTo(i);
          return true;
        }
      }
    }
    if (location - Floor::BOTTOM < speed) return false;

    else {
      location -= speed;
      return true;
    }
  }
  else {
    return false;
  }
}
