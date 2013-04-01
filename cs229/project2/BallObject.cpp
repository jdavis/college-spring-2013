#include <iostream>
#include "BallObject.h"

// set up defaults
BallObject::BallObject() {
	color = "blue";
}

int BallObject::moveDistance() {
	return 1;
}

bool BallObject::stopsMovableObjects() {
	return true;
}

bool BallObject::isSeeable() {
	return true;
}

SimSquareAction BallObject::objectEnteredSquare(IEnvObject *obj) {
	if (obj->getType() == SimTypeRobot)
		return SimMoveEntity;
	else return SimDoNothing;
}

int BallObject::setValueForProperty(string &v, string &p) {
	if (!p.length()) return 1;
	if (!v.length()) return 1;
	if (p == "color") color = v;
	else return 1;

	return 0;
}

SimType BallObject::getType() {
	return SimTypeBall;
}

string BallObject::description() {
	return "\nColor " + color;
}

string BallObject::getDisplay() {
	string disp = "";
	if (color.size()) disp.push_back(toupper(color[0]));
	disp.push_back('B');
	return disp;
}
