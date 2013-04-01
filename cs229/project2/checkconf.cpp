#include <iostream>
#include "Interfaces.h"
#include "Simulation.h"

using namespace std;

// since our simulator handles most of the things
// we just have to pass it the arg and then let it do the rest
int main(int argc, const char *argv[]) {
	Simulation *sim = new Simulation();

	if (argc != 2) {
		cout << "please supply a conf file" << endl;
		return 1;
	}

	sim->loadConfiguration(argv[1]);
	sim->printGrid();
	sim->listObjects();

	return 0;
}
