#include <iostream>
#include "EnergyObject.h"
#include "RobotObject.h"

// default is 5 according to Jim on WebCT
EnergyObject::EnergyObject() {
	energy = 5;
}

int EnergyObject::moveDistance() {
	return 1;
}

bool EnergyObject::stopsMovableObjects() {
	return 1;
}

bool EnergyObject::isSeeable() {
	return true;
}

// add the energy and then remove the pill from the grid
SimSquareAction EnergyObject::objectEnteredSquare(IEnvObject *obj) {
	if (obj->getType() == SimTypeRobot) {
		RobotObject *robo = (RobotObject *) obj;

		robo->setEnergy(robo->getEnergy() + energy);

		return SimRemoveSelf;
	} else {
		return SimDoNothing;
	}
}

int EnergyObject::setValueForProperty(string &v, string &p) {
	if (!p.length()) return 1;
	if (!v.length()) return 1;
	int propValue = atoi(v.c_str());

	if (p == "energy") {
		energy = propValue;
	} else {
		return 1;
	}

	return 0;
}

SimType EnergyObject::getType() {
	return SimTypeEnergyPill;
}

string EnergyObject::description() {
	return "";
}

string EnergyObject::getDisplay() {
	return "EP";
}
