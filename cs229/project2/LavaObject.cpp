#include <iostream>
#include "LavaObject.h"
#include "RobotObject.h"

LavaObject::LavaObject() {
	damage = 5;
}

int LavaObject::moveDistance() {
	return 0;
}

bool LavaObject::stopsMovableObjects() {
	return 0;
}

bool LavaObject::isSeeable() {
	return false;
}

// lava just damages the robot unless its energy is at zero, then it destroys it
SimSquareAction LavaObject::objectEnteredSquare(IEnvObject *obj) {
	if (obj->getType() == SimTypeRobot) {
		RobotObject *robo = (RobotObject *) obj;
		int energy = robo->getEnergy() - damage;

		if (energy < 0) energy = 0;

		robo->setEnergy(energy);

		if (energy == 0) return SimRemoveEntity;
		else return SimDoNothing;
	} else {
		return SimDoNothing;
	}
}

int LavaObject::setValueForProperty(string &v, string &p) {
	if (!p.length()) return 1;
	if (!v.length()) return 1;
	int propValue = atoi(v.c_str());

	if (p == "damage") {
		damage = propValue;
	} else {
		return 1;
	}

	return 0;
}

SimType LavaObject::getType() {
	return SimTypeLava;
}

string LavaObject::description() {
	return "";
}

string LavaObject::getDisplay() {
	return "RO";
}
