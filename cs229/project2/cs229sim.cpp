#include <iostream>
#include "Interfaces.h"
#include "Simulation.h"
#include "SearchRobot.h"

using namespace std;

// load the conf and then simulate it with the robots
int main(int argc, const char *argv[])
{
	Simulation sim;
	SearchRobot robo;

	if (argc != 2) {
		cout << "please supply a conf file" << endl;
		return 1;
	}

	sim.loadConfiguration(argv[1]);

	sim.printGrid();
	sim.setRobot(0, robo);

	sim.simulateWorld();
	
	return 0;
}
