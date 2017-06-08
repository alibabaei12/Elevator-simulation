
// identification comments code block
// Programmer: Ali Babaei
// Programmer's ID: 1447397

#include <iostream>
#include <string>
#include <vector>
using namespace std;

#include <cstdlib>
#include <ctime>

#include "Rider.h"
#include "Building.h"
#include "Floor.h"
#include "Panel.h"

int main()
{
  srand(time(0)); rand();

  // Seed elevators with riders so their doors open for riders to disembark
  for (int i = 0; i < 3; i++)
  {
    Building::elevators[1].board(Rider(4, 1)); // load middle elevator with down-riders to disembark at time zero
    Building::elevators[2].board(Rider(0, 2)); // load right-most elevator with up-riders to disembark at time zero
  }

  for (int i = 0;; i++)
  {
    cout << "-----------------------------------------------\n";
    cout << "-- Time " << i << " ---------------------------\n";
    for (int elevator = 0; elevator < Building::ELEVATORS; elevator++)
       cout << Building::elevators[elevator] << endl;

    for (int floor = 0; floor < Building::FLOORS; floor++)
       cout << Building::floors[floor] << endl;

    // 20 riders per second from time 10 to time 20 -- approx 200 total riders
    //Building::action(10 < i && i < 20 ? 20 : 0);
    Building::action(3 < i && i < 10 ? 20 : 0);
        //Building::action(i < 300 ? 1 : 0);
    cin.get();
  }
}
