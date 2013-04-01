#include <iostream>
#include "WaterObject.h"
#include "RobotObject.h"

WaterObject::WaterObject() {
	damage = 1;
}

int WaterObject::moveDistance() {
	return 0;
}

bool WaterObject::stopsMovableObjects() {
	return 0;
}

bool WaterObject::isSeeable() {
	return false;
}

// water just removes energy from the robot
SimSquareAction WaterObject::objectEnteredSquare(IEnvObject *obj) {
	if (obj->getType() == SimTypeRobot) {
		RobotObject *robo = (RobotObject *) obj;
		int energy = robo->getEnergy() - damage;

		if (energy < 0) energy = 0;

		robo->setEnergy(energy);

		return SimDoNothing;
	} else {
		return SimDoNothing;
	}
}

int WaterObject::setValueForProperty(string &v, string &p) {
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

SimType WaterObject::getType() {
	return SimTypeWater;
}

string WaterObject::description() {
	return "";
}

string WaterObject::getDisplay() {
	return "WP";
}
