#include <iostream>
#include <map>
#include <string>
#include "Interfaces.h"
#include "Simulation.h"
#include "SimEntity.h"

using namespace std;

int main(int argc, const char *argv[])
{
	Simulation sim;
	sim.loadSafeZoneGame();

	// trying to do this progammatically by iterating over a mp
	map<string, int> simObjects;
	map<string, int> safeZoneObjects;

	// normal objects
	simObjects["rock"] = 10;
	simObjects["hole"] = 3;
	simObjects["lava"] = 1;
	simObjects["water"] = 3;
	simObjects["mud"] = 3;
	simObjects["fog"] = 5;
	simObjects["jam"] = 4;
	simObjects["energy"] = 2;

	// safe zone objects
	safeZoneObjects["ball"] = 3;
	safeZoneObjects["block"] = 3;
	safeZoneObjects["robot"] = 1;

	map<string, int>::iterator it;

	// standard simulation stuff
	cout << "<Simulation>" << endl;
	cout << "width = 30" << endl;
	cout << "height = 10" << endl;
	cout << "steps = 300" << endl;
	cout << "</Simulation>" << endl << endl;

	// create the new objects and then randomly add it to the sim
	for(it = simObjects.begin(); it != simObjects.end(); it++) {
		string type = (*it).first;
		int count = (*it).second;

		for(int f = 0; f < count; f++) {
			SimEntity *entity = new SimEntity(type);
			sim.randomlyAddInSim(entity, 0);
		}
	}

	// add the save zone objects but first, add a color for each one
	for(it = safeZoneObjects.begin(); it != safeZoneObjects.end(); it++) {
		string type = (*it).first;
		int count = (*it).second;

		for(int f = 0; f < count; f++) {
			SimEntity *blue = new SimEntity(type);

			string prop = "color";
			string color = "blue";

			blue->setValueForProperty(color, prop);
			sim.randomlyAddInSim(blue, 1);

			color = "red";
			SimEntity *red = new SimEntity(type);
			red->setValueForProperty(color, prop);
			sim.randomlyAddInSim(red, -1);
		}
	}

	// print out our config file
	sim.printConfiguration();
	
	return 0;
}
