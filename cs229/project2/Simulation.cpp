#include <string>
#include <vector>
#include <map>
#include <list>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <stdlib.h>
#include "Interfaces.h"
#include "Simulation.h"
#include "RobotObject.h"
#include "Sight.h"
#include "NormalProbe.h"
#include "EmptyProbe.h"

Simulation::Simulation() {
	width = height = steps = 0;
	successfulLoad = false;

	robots = new list<pair<IRobot *, SimEntity *> *>;

	// create our placement map
	placementMap = new int[SimTypeLast + 1];
	
	// each object has a 1 if the value can be placed concurrently in the same square
	// there might be a few minor errors...
	placementMap[SimTypeRobot] = 	(1 << SimTypeLava) |
									(1 << SimTypeWater) |
									(1 << SimTypeMud) |
									(1 << SimTypeHole) |
									(1 << SimTypeEnergyPill);
	placementMap[SimTypeRock] = 0;

	placementMap[SimTypeLava] = 	(1 << SimTypeRobot) |
									(1 << SimTypeBall) |
									(1 << SimTypeBlock);

	placementMap[SimTypeWater] = 	(1 << SimTypeBall) |
									(1 << SimTypeBlock) |
									(1 << SimTypeRobot) |
									(1 << SimTypeEnergyPill);

	placementMap[SimTypeMud] = placementMap[SimTypeWater];

	placementMap[SimTypeBall] = 	(1 << SimTypeWater) |
									(1 << SimTypeMud) |
									(1 << SimTypeHole);

	placementMap[SimTypeBlock] = placementMap[SimTypeBall];

	placementMap[SimTypeHole] = 0;

	placementMap[SimTypeEnergyPill] = 	(1 << SimTypeWater) |
										(1 << SimTypeMud);
	placementMap[SimTypeFog] = 0;
	placementMap[SimTypeJam] = 0;
}

void Simulation::loadSafeZoneGame() {
	// the safe zone game thing always has the same values
	width = 30;
	height = 10;
	steps = 300;

	successfulLoad = true;
	createGrid();
}

void Simulation::loadConfiguration(string file) {
	ifstream f(file.c_str());
	string line;


	bool inElement = 0;
	list<map<string, string>* > objects;
	map<string, string> *simulation = 0;
	string name;

	map<string, string> *object = 0;
	while(f.good()) {
		getline(f, line);
		
		if (!line.length()) continue;
		
		name = findElementName(line);
		
		if (name.length()) {
			// check the name
			inElement = !(name[0] == '/');

			if (!inElement) {
				continue;
			} else {
				if (object) objects.push_back(object);
				object = new map<string, string>();

				if (name == "simulation") {
					if (!simulation) simulation = object;
					else cout << "error: multiple simulations found" << endl;
				}
			}
		}
		
		if (inElement) {
			string key = findProp(line);
			string value = findValue(line);

			(*object)[key] = value;
		}
	}

	if (object) objects.push_back(object);
	object = new map<string, string>();

	if (simulation->find("width") == simulation->end()) {
		cout << "no width in simulation tags" << endl;
		return;
	}

	if (simulation->find("height") == simulation->end()) {
		cout << "no height in simulation tags" << endl;
		return;
	}

	if (simulation->find("steps") == simulation->end()) {
		cout << "no step in simulation tags" << endl;
		return;
	}

	width = atoi(simulation->find("width")->second.c_str());
	height = atoi(simulation->find("height")->second.c_str());
	steps = atoi(simulation->find("steps")->second.c_str());

	if (simulation->size() > 4) {
		cout << "extra tags in simulation" << endl;
		return;
	}

	createGrid();

	list<map<string, string>* >::iterator it = objects.begin();
	map<string, string>::iterator mapIt;

	for(it = objects.begin(); it != objects.end(); it++) {
		// each value/propety in the config file is stored as a map
		// that way, we can pull out the values whenever we want to and
		// so that there is no worry about which values come first

		map<string, string> *o = *it;

		map<string, string>::iterator find = o->find("type");

		if (find == o->end() && o->find("width") != o->end()) continue;

		// check for the required properties in all elements but the simulation
		if (find == o->end()) {
			cout << "No type property" << endl;
			return;
		}

		if (o->find("xloc") == o->end()) {
			cout << "No xloc property" << endl;
			return;
		}

		if (o->find("yloc") == o->end()) {
			cout << "No yloc property" << endl;
			return;
		}

		if (o->find("display") == o->end()) {
			cout << "No display property" << endl;
			return;
		}

		// make sure the x and y are valid values
		int x = atoi(o->find("xloc")->second.c_str());
		int y = atoi(o->find("yloc")->second.c_str());

		if (x < 0 || x >= width) {
			cout << "invalid xloc" << endl;
			return;
		}

		if (y < 0 || y >= height) {
			cout << "invalid yloc" << endl;
			return;
		}
		

		// create the SimEntity for the name in the config file
		SimEntity *newObj = new SimEntity(find->second);

		// make sure the type was valid
		if (newObj->isInvalid()) {
			cout << "invalid type " << find->second << endl;
			return;
		}

		// go through each property and set the values
		for(mapIt = o->begin(); mapIt != o->end(); mapIt++) {
			string property = (*mapIt).first;
			string value = (*mapIt).second;

			// check to see if it is an invalid value
			float floatVal = atof(value.c_str());

			if (floatVal < 0) {
				cout << "invalid value: " + value << endl;
				return;
			}

			if (property.length()) {
				if (newObj->setValueForProperty(value, property)) {
					cout << "invalid property: " + property << endl;
					return;
				}
			}
		}

		int w = newObj->getXLoc();
		int h = newObj->getYLoc();

		// make sure it goes into the grid
		if (w >= 0 && w < width &&
				h >= 0 && h < height) {
			Square sq = grid[h][w];
			int mask = placementMap[newObj->getType()];

			if (sq.canPlaceObjectWithMask(*newObj, mask)) {
				sq.addEntity(newObj);
			} else {
				cout << "invalid position for " + newObj->getName() << endl;
				return;
			}

			// add the frame for the robot in our list, the brain hasn't been set yet
			if (newObj->getType() == SimTypeRobot) {
				pair<IRobot *, SimEntity *> *p = new pair<IRobot *, SimEntity *>;
				p->first = NULL;
				p->second = newObj;
				robots->push_back(p);
			}
		}
	}

	// initialize our variables if we loaded the config successfully
	robotsSet = 0;
	successfulLoad = true;
	movesForward = 0;
	didProbe = new int[robots->size()];
	for(unsigned int d = 0; d < robots->size(); d++) {
		didProbe[d] = 0;
	}
}

void Simulation::setRobot(int index, IRobot & r) {
	list<pair<IRobot *, SimEntity *> *>::iterator it;

	int f;
	// add the brain for the robot
	for(it = robots->begin(), f = 0; it != robots->end(); it++, f++) {
		if (index == f)
			(*it)->first = &r;
	}

	robotsSet++;
}

void Simulation::step(int s) {
	// do a few checks first
	if (!successfulLoad) {
		cout << "unsuccessful load" << endl;
		return;
	}

	if (robotsSet != (int)robots->size()) {
		cout << "Not enough robots added" << endl;
	}


	for(int step = 0; step < s; step++) {
		list<pair<IRobot *, SimEntity *> *>::iterator it;

		int f;
		for(it = robots->begin(), f = 0; it != robots->end(); it++, f++) {
			IRobot *brain = (*it)->first;
			SimEntity *body = (*it)->second;

			if (brain == NULL) continue;

			RobotObject *robo = (RobotObject *) body->getObject();
			
			Square sq = grid[body->getYLoc()][body->getXLoc()];

			IProbe *probe;

			if (didProbe[f]) probe = new NormalProbe(body, grid, didProbe[f], width, height);
			else if (sq.affectsProbe()) probe = sq.probe();
			else probe = new EmptyProbe();

			didProbe[f] = 0;
			
			ISee *sight;
			if(sq.affectsSight()) sight = sq.sight();
			else sight = new Sight(body, grid, width, height);

			IMove *robotMove = &(brain->getMove(*sight, *probe));
			
			SimDirection dir = robo->getDirection();
			int x = body->getXLoc();
			int y = body->getYLoc();

			//cout << "robot direction = " << dir << endl;
			//cout << "Action = " << robotMove->getAction() << endl;
			int parameter = robotMove->getParameter();
			switch(robotMove->getAction()) {
				case SimRobotStay:
					moveBall(x + xChange(dir), y + yChange(dir), dir);
					break;
				case SimRobotForward:
					if (robo->canMove()) {
						robo->moveForward();
						if (canMove(x, y, dir)) move(x, y, dir);
						movesForward++;
					}
					break;
				case SimRobotTurnLeft:
					robo->turnLeft();
					moveBall(x + xChange(dir), y + yChange(dir), dir);
					break;
				case SimRobotTurnRight:
					robo->turnRight();
					moveBall(x + xChange(dir), y + yChange(dir), dir);
					break;
				case SimRobotProbe:
					robo->fireProbe(parameter);
					didProbe[f] = parameter;
					moveBall(x + xChange(dir), y + yChange(dir), dir);
					break;
				case SimRobotPulse:
					robo->fireBeam(parameter);
					firePulseBeam(body, parameter);
					moveBall(x + xChange(dir), y + yChange(dir), dir);
					break;
			}

			robo->rechargeEnergy();
		}

	}
}

bool Simulation::canMove(int x, int y, SimDirection dir) {
	int dx = xChange(dir);
	int dy = yChange(dir);

	int newX = x + dx;
	int newY = y + dy;

	if (newX >= width || newY >= height || newX == -1 || newY == -1) return false;

	Square sq = grid[newY][newX];

	// check the next square as well
	if (sq.canMoveInto()) return true;
	else if (sq.acceptsMovableObjects()) return canMove(newX, newY, dir);
	else return false;
}

void Simulation::moveBall(int x, int y, SimDirection dir) {
	// only move forward if it can
	if (!movesForward) return;
	movesForward--;

	int dx = xChange(dir);
	int dy = yChange(dir);

	int newX = x + dx;
	int newY = y + dy;

	if (newX >= width || newY >= height || newX < 0 || newY < 0) return;

	Square sq = grid[y][x];
	Square newSq = grid[newY][newX];
	SimEntity *ent = sq.entityToMove();

	// silly checks that make the code ugly
	if (ent == NULL) {
		movesForward = 0;
		return;
	}
	
	if (ent->getType() != SimTypeBall) {
		movesForward = 0;
		return;
	}

	if (!canMove(x, y, dir)) return;
	else if (newSq.entityToMove() != NULL) return;

	sq.removeEntity(ent);
	newSq.addEntity(ent);

	ent->setXLoc(newX);
	ent->setYLoc(newY);

	moveBall(newX, newY, dir);
}

void Simulation::move(int x, int y, SimDirection dir) {
	int dx = xChange(dir);
	int dy = yChange(dir);

	int newX = x + dx;
	int newY = y + dy;

	// bounds checking
	if (newX >= width || newY >= height || newX < 0 || newY < 0) return;

	Square sq = grid[y][x];
	Square newSq = grid[newY][newX];
	SimEntity *ent = sq.entityToMove();

	sq.removeEntity(ent);
	SimSquareAction action = newSq.addEntity(ent);
	SimEntity *energy;
	
	switch(action) {
		case SimRemoveEntity:
			newSq.removeEntity(ent);
			return;
		case SimRemoveSelf:
			energy = newSq.entityToMove();
			newSq.removeEntity(energy);
			break;
		case SimDoNothing:
		case SimMoveEntity:
			// these are handled naturally
			break;
	}

	ent->setXLoc(newX);
	ent->setYLoc(newY);

	// start it all over again
	if (newSq.entityToMove() != ent) move(newX, newY, dir);
}

int Simulation::xChange(SimDirection dir) {
	return (dir == SimRight) - (dir == SimLeft);
}

int Simulation::yChange(SimDirection dir) {
	return (dir == SimDown) - (dir == SimUp);
}

void Simulation::createGrid() {
	// create the grid, pointers to pointers, yay
	grid = new Square*[height];
	for(int h = 0; h < height; h++) {
		grid[h] = new Square[width];
	}
}

void Simulation::firePulseBeam(SimEntity *e, int power) {
	// checks in the path of the robot to see if the beam hits another robot
	RobotObject *obj = (RobotObject *) e->getObject();
	int x = e->getXLoc();
	int y = e->getYLoc();
	SimDirection dir = obj->getDirection();
	int deltaX = xChange(dir);
	int deltaY = yChange(dir);

	while(x < (width - deltaX) && y < (height - deltaY) && x - deltaX < 0 && y - deltaY < 0) {
		x += deltaX;
		y += deltaY;
		Square sq = grid[y][x];
		list<SimEntity *> *l = sq.allEntities();
		list<SimEntity *>::iterator it;
		if (l == NULL) continue;
		for(it = l->begin(); it != l->end(); it++) {
			SimEntity *e = *it;
			// we made a hit! remove the energy from the other robot
			if (e->getType() == SimTypeRobot) {
				RobotObject *ent = (RobotObject *) (*it)->getObject();
				ent->hitByBeam(power);
			}
		}
	}
}

void Simulation::simulateWorld() {
	step(steps);
}

void Simulation::printGrid() {
	if (!successfulLoad) return;
	for(int h = 0; h < height; h++) {
		for(int w = 0; w < width; w++)  {
			cout << grid[h][w].shortDescription() << " ";
		}
		cout << endl;
	}
}

void Simulation::listObjects() {
	if (!successfulLoad) return;
	for(int h = 0; h < height; h++) {
		for(int w = 0; w < width; w++)  {
			Square sq = grid[h][w];
			if (sq.getSize()) {
				// print out the location and descxription below it
				cout << "Location " << h << ", " << w << endl;
				cout << sq.longDescription() << endl << endl;
			}
		}
	}
}

void Simulation::printConfiguration() {
	if (!successfulLoad) return;
	for(int h = 0; h < height; h++) {
		for(int w = 0; w < width; w++)  {
			cout << grid[h][w].configDescription();
		}
	}
}

// just randomly tries to find a place to put the new object
void Simulation::randomlyAddInSim(SimEntity *e, int zone) {
	int x, y;
	int xMod = 4, yMod = 8, xStart, yStart;
	//cout << "Type got = " << e->getType() << endl;
	int mask = placementMap[e->getType()];
	Square sq;

	if (zone == -1) { // left
		xStart = 1;
		yStart = 1;
	} else if (zone == 0) { // middle
		xStart = 5;
		xMod = 20;
		yStart = 0;
		yMod = 10;
	} else if (zone == 1) { // right
		xStart = 25;
		yStart = 1;
	}
	
	do {
		x = xStart + rand() % xMod;
		y = yStart + rand() % yMod;
		
		sq = grid[y][x];
		e->setXLoc(x);
		e->setYLoc(y);
	} while(!sq.canPlaceObjectWithMask(*e, mask));

	sq.addEntity(e);
}

// the configuration helper methods
// looks for a name in brackets, case insensitive
string Simulation::findElementName(string l) {
	bool inBrackets = 0;
	unsigned int f;
	string name;
	for(f = 0; f < l.length(); f++) {
		char c = tolower(l[f]);

		if (c == '<') {
			if (inBrackets) return "";

			inBrackets = 1;
		} else if (c == '>') {
			if (!inBrackets) return "";
			inBrackets = 0;
			break;
		} else if (inBrackets) {
			name.push_back(c);
		}
	}
	
	if (inBrackets) return "";

	return name;
}

// checks to make sure it isn't a comment and then returns the
// value infront of the equals sign
string Simulation::findProp(string &l) {
	string name;

	size_t equals = l.find("=");
	size_t comment = l.find("//");
	size_t f;

	if (equals == string::npos) return name;
	if (equals > comment) return "";

	for(f = l.find_first_not_of(" \t"); f < equals; f++) {
		char c = l[f];

		if (!isspace(c)) {
				name.push_back(c);
		} else {
			return name;
		}
	}

	return trim(name);
}

// returns the value after the equals sign
string Simulation::findValue(string &l) {
	string name;

	size_t equals = l.find("=");
	size_t comment = l.find("//");
	size_t f;

	if (equals == string::npos) return name;
	if (equals > comment) return "";

	for(f = equals + 2; f < l.length() && f != comment; f++) {
		char c = l[f];

		name.push_back(c);
	}

	return trim(name);
}

// removes all ending white space
string Simulation::trim(string s) {
	size_t end = s.find_last_not_of(" \r\n\t");
	string n;
	if (end != string::npos) n = s.substr(0, end + 1);
	else n = s;
	return n;
}
