#ifndef _SIMULATION
#define _SIMULATION

#include <string>
#include <list>
#include "Interfaces.h"
#include "Square.h"
#include "SimEntity.h"

class Simulation : ISimulation {
	public:
		// our constructor to set up initial variables
		Simulation();
		
		// called by outside programs
		// it sets up a ton of things for us, like the grid of squares
		// and all of the objects in the config file
		void loadConfiguration(string file);

		// used for ./create
		void loadSafeZoneGame();

		// sets the body of the robot with the brain
		void setRobot(int index, IRobot &r);

		// simulate!
		void step(int s);

		// runs the complete simulation
		void simulateWorld();

		// prints out a grid of squares to see what everything looks like
		void printGrid();

		// prints out the objects according to their location and a short description
		void listObjects();
		
		// outputs all of the config information that has been setup, used in ./create
		void printConfiguration();

		// used in create
		void randomlyAddInSim(SimEntity *e, int zone);
	private:
		// essential simulation variables
		int width, height, steps;

		// the grid for the simulation area
		Square **grid;

		// keeep track of all of the robots set so we can error if not enough have been added
		int robotsSet;

		// the array to determine if an object can go in a square
		int *placementMap;

		// indicates if the robot should be given a probe on its next turn
		int *didProbe;

		// the robot brains and their bodies
		list<pair<IRobot *, SimEntity *> *> *robots;

		// indicates if the simulation loaded without errors
		bool successfulLoad;

		// pesky balls cause trouble...
		void moveBall(int x, int y, SimDirection dir);

		// the number of consecutive moves forward the robot has made
		int movesForward;
		
		// sets everything up
		void createGrid();

		// to hurt other robots
		void firePulseBeam(SimEntity *e, int power);

		// get the delta values for the direction
		int xChange(SimDirection dir);
		int yChange(SimDirection dir);

		// indicates if an object can move, recursive
		bool canMove(int x, int y, SimDirection dir);

		// moves objects recursively
		void move(int x, int y, SimDirection dir);

		// private methods for parsing a config file
		string findElementName(string l);
		string findProp(string &l);
		string findValue(string &l);
		string trim(string s);
};

#endif
