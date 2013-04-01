#include <iostream>
#include "RockObject.h"

int RockObject::moveDistance() {
	return 0;
}

bool RockObject::stopsMovableObjects() {
	return true;
}

bool RockObject::isSeeable() {
	return true;
}

// a object can never enter the square
SimSquareAction RockObject::objectEnteredSquare(IEnvObject *obj) {
	return SimDoNothing;
}

int RockObject::setValueForProperty(string &v, string &p) {
	return 1;
}

SimType RockObject::getType() {
	return SimTypeRock;
}

string RockObject::description() {
	return "";
}

string RockObject::getDisplay() {
	return "RO";
}
