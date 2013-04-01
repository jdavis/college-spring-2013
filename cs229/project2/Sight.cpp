#include "Sight.h"
#include "RobotObject.h"
#include <iostream>
#include <vector>

Sight::Sight(SimEntity *robot, Square **g, int w, int h) {
	// set up the variables so when look is called, it will generate everything then
	grid = g;
	width = w;
	height = h;
	x = robot->getXLoc();
	y = robot->getYLoc();
	RobotObject *r = (RobotObject *) robot->getObject();
	direction = r->getDirection();
}

Sight::~Sight() {
	//delete l;
}


list<ISimObject *>& Sight::look(int f) {
	list<ISimObject *> *ret = new list<ISimObject *>;
	int dx = xChange(f);
	int dy = yChange(f);

	int newX = dx + x;
	int newY = dy + y;

	if (newX >= width || newY >= height || newX < 0 || newY < 0) return *(ret);

	Square sq = grid[newY][newX];

	list<SimEntity *> *entities = sq.allEntities();

	if (entities == NULL) return *(ret);

	list<SimEntity *>::iterator it;

	// get all of the entities in the square and put them into the list
	for(it = entities->begin(); it != entities->end(); it++) {
		ISimObject *obj = (ISimObject *) *(it);
		ret->push_back(obj);
	}

	return *(ret);
}

// ugly code
int Sight::xChange(int f) {
	int dx;

	// since the direction changes, we need to take that into consideration
	// there probably is a few line algorithm for this, but i'm a little pressed for time
	if (direction == 0) {
		if (f == 7 || f == 6 || f == 5) dx = -1;
		else if (f == 1 || f == 2 || f == 3) dx = 1;
		else dx = 0;
	} else if (direction == 1) {
		if (f == 7 || f == 0 || f == 1) dx = 1;
		else if (f == 5 || f == 4 || f == 3) dx = -1;
		else dx = 0;
	} else if (direction == 2) {
		if (f == 7 || f == 6 || f == 5) dx = 1;
		else if (f == 1 || f == 2 || f == 3) dx = -1;
		else dx = 0;
	} else if (direction == 3) {
		if (f == 7 || f == 0 || f == 1) dx = -1;
		else if (f == 5 || f == 4 || f == 3) dx = 1;
		else dx = 0;
	}

	return dx;
}

int Sight::yChange(int f) {
	int dy;

	// since the direction changes, we need to take that into consideration
	// there probably is a few line algorithm for this, but i'm a little pressed for time
	if (direction == 0) {
		if (f == 7 || f == 0 || f == 1) dy = -1;
		else if (f == 5 || f == 4 || f == 3) dy = 1;
		else dy = 0;
	} else if (direction == 1) {
		if (f == 7 || f == 6 || f == 5) dy = -1;
		else if (f == 1 || f == 2 || f == 3) dy = 1;
		else dy = 0;
	} else if (direction == 2) {
		if (f == 7 || f == 0 || f == 1) dy = 1;
		else if (f == 5 || f == 4 || f == 3) dy = -1;
		else dy = 0;
	} else if (direction == 3) {
		if (f == 7 || f == 6 || f == 5) dy = 1;
		else if (f == 1 || f == 2 || f == 3) dy = -1;
		else dy = 0;
	}

	return dy;
}
