#include <iostream>
#include "HoleObject.h"
#include "RobotObject.h"

int HoleObject::moveDistance() {
	return 0;
}

bool HoleObject::stopsMovableObjects() {
	return 0;
}

bool HoleObject::isSeeable() {
	return false;
}

// remove anything that moves onto the hole
SimSquareAction HoleObject::objectEnteredSquare(IEnvObject *obj) {
	return SimRemoveEntity;
}

int HoleObject::setValueForProperty(string &v, string &p) {
	return 1;
}

SimType HoleObject::getType() {
	return SimTypeHole;
}

string HoleObject::description() {
	return "";
}

string HoleObject::getDisplay() {
	return "H";
}
