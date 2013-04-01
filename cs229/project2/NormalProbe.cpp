#include "NormalProbe.h"
#include "SimEntity.h"
#include "RobotObject.h"
#include <iostream>

NormalProbe::NormalProbe(SimEntity *robot, Square **g, int w, int width, int height) {
	RobotObject *r = (RobotObject *) robot->getObject();
	sWidth = width;
	sHeight = height;
	grid = g;

	int x = robot->getXLoc();
	int y = robot->getYLoc();

	SimDirection direction = r->getDirection();

	int dx = (direction == SimRight) - (direction == SimLeft);
	int dy = (direction == SimDown) - (direction == SimUp);

	int newX = dx + x;
	int newY = dy + y;

	if (newX >= width || newY >= height || newX < 0 || newY < 0) return;

	Square sq = grid[newY][newX];

	l = new list<ISimObject *>;

	w %= 10;

	// move the beam in the correct order
	for(int f = 0; f < w; f++) {
		int m = (float)f / 2.0 + .5;
		l->push_back(scanAlong(x - (f % 2 ? dy : -1 * m * dy), y - (f % 2 ? dx * m : -1 * m * dx), dx, dy));
	}
}

NormalProbe::~NormalProbe() {
	//delete l;
}

ISimObject *NormalProbe::scanAlong(int x, int y, int dx, int dy) {
	if (x >= sWidth || y >= sHeight || x < 0 || y < 0) return 0;

	Square sq;

	// scan along until we get to the end of else we find a seeable Object
	while(1) {
		x += dx;
		y += dy;

		if (x >= sWidth || y >= sHeight || x < 0 || y < 0) return 0;

		sq = grid[y][x];

		list<SimEntity *> *entities = sq.allEntities();
		if (entities == NULL) continue;

		list<SimEntity *>::iterator it;

		for(it = entities->begin(); it != entities->end(); it++) {
			SimEntity *sim = *it;
			IEnvObject *obj = sim->getObject();

			if (obj->isSeeable()) return (ISimObject *) sim;
		}
	}


}

list<ISimObject *>& NormalProbe::probe() {
	return *l;
}
