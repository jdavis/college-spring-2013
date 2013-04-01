#include <iostream>
#include "RobotObject.h"
#include "SimEntity.h"
#include <sstream>

// set our defaults
RobotObject::RobotObject() {
	energy = 100;
	recharge = 1;
	moveCost = 1;
	turnCost = 1;
	probeCost = 1;
	paramA = 0;
	paramB = 1;
	paramC = 1;
	direction = SimUp;
	color = "blue";
	stuckFor = 0;
}

int RobotObject::moveDistance() {
	return 1;
}

bool RobotObject::stopsMovableObjects() {
	return true;
}

bool RobotObject::isSeeable() {
	return true;
}

int RobotObject::getEnergy() {
	return energy;
}

void RobotObject::setEnergy(int e) {
	energy = e;
}

SimSquareAction RobotObject::objectEnteredSquare(IEnvObject *obj) {
	return SimMoveEntity;
}

// change our defaults if the config says to
int RobotObject::setValueForProperty(string &v, string &p) {
	if (!p.length()) return 1;
	if (!v.length()) return 1;

	int propValue = atoi(v.c_str());

	if (p == "energy") {
		energy = propValue;
	} else if (p == "recharge") {
		recharge = propValue;
	} else if (p == "movecost") {
		moveCost = propValue;
	} else if (p == "turncost") {
		turnCost = propValue;
	} else if (p == "probecost") {
		probeCost = propValue;
	} else if (p == "parmA") {
		paramA = atof(v.c_str());
	} else if (p == "parmB") {
		paramB = atof(v.c_str());
	} else if (p == "parmC") {
		paramC = atof(v.c_str());
	} else if (p == "color") {
		color = v;
	} else {
		return 1;
	}

	return 0;
}

SimType RobotObject::getType() {
	return SimTypeRobot;
}

// robots have a special description
// we want to see their energy as well as their color
string RobotObject::description() {
	stringstream estream;
	estream << energy;
	return "\nEnergy " + estream.str() + "\n" + "Color " + color;
}

// if the robot is colored, we want to print that as well
string RobotObject::getDisplay() {
	string disp = "";
	if (color.size()) disp.push_back(toupper(color[0]));
	disp.push_back('R');
	return disp;
}

// see if we can move
bool RobotObject::canMove() {
	if (stuckFor) stuckFor--;
	else if (energy > moveCost) return true;
	
	return false;
}

// used by objects like mud
void RobotObject::setStuckFor(int s) {
	stuckFor = s;
}

// remove energy for the actions
void RobotObject::moveForward() {
	energy -= moveCost;
	if (energy < 0) energy = 0;
}

void RobotObject::turnLeft() {
	energy -= turnCost;
	if (energy < 0) energy = 0;
	direction -= 1;

	if (direction == -1) direction = 3;
}

void RobotObject::turnRight() {
	energy -= turnCost;
	if (energy < 0) energy = 0;
	direction += 1;

	if (direction == 4) direction = 0;
}

// the energy is recharged every turn
void RobotObject::rechargeEnergy() {
	energy += recharge;
}

void RobotObject::fireProbe(int width) {
	energy -= width * probeCost;
	if (energy < 0) energy = 0;
}


void RobotObject::fireBeam(int e) {
	energy -= paramA + e * paramB;
	if (energy < 0) energy = 0;
}

void RobotObject::hitByBeam(int e) {
	// the equation from the pdf
	energy -= paramC * e;
}

SimDirection RobotObject::getDirection() {
	return (SimDirection) direction;
}
