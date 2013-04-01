#include <iostream>
#include "MudObject.h"
#include "RobotObject.h"

MudObject::MudObject() {
	damage = 5;
	delay = 3;
}

int MudObject::moveDistance() {
	return 0;
}

bool MudObject::stopsMovableObjects() {
	return 0;
}

bool MudObject::isSeeable() {
	return false;
}

// mud removes energy AND prevents it from moving for a certain delay
SimSquareAction MudObject::objectEnteredSquare(IEnvObject *obj) {
	if (obj->getType() == SimTypeRobot) {
		RobotObject *robo = (RobotObject *) obj;
		int energy = robo->getEnergy() - damage;

		if (energy < 0) energy = 0;

		robo->setEnergy(energy);
		robo->setStuckFor(delay);

		return SimDoNothing;
	} else {
		return SimDoNothing;
	}
}

int MudObject::setValueForProperty(string &v, string &p) {
	if (!p.length()) return 1;
	if (!v.length()) return 1;
	int propValue = atoi(v.c_str());

	if (p == "damage") {
		damage = propValue;
	} else if (p == "delay") {
		delay = propValue;
	} else {
		return 1;
	}

	return 0;
}

SimType MudObject::getType() {
	return SimTypeMud;
}

string MudObject::description() {
	return "";
}

string MudObject::getDisplay() {
	return "MS";
}
