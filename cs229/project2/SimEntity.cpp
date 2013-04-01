#include <iostream>
#include <sstream>
#include "SimEntity.h"
#include "RobotObject.h"
#include "RockObject.h"
#include "LavaObject.h"
#include "WaterObject.h"
#include "MudObject.h"
#include "BallObject.h"
#include "BlockObject.h"
#include "HoleObject.h"
#include "EnergyObject.h"
#include "FogProperty.h"
#include "JamProperty.h"

SimEntity::SimEntity(string &t) {
	// set up our inital variables
	object = NULL;
	property = NULL;
	name = "Object";
	color = "";
	invalidType = false;

	type = t;

	// check the type and then do something if it doesn't exist
	if (t == "robot") {
		object = new RobotObject();
	} else if (t == "rock") {
		object = new RockObject();
	} else if (t == "lava") {
		object = new LavaObject();
	} else if (t == "water") {
		object = new WaterObject();
	} else if (t == "mud") {
		object = new MudObject();
	} else if (t == "ball") {
		object = new BallObject();
	} else if (t == "block") {
		object = new BlockObject();
	} else if (t == "hole") {
		object = new HoleObject();
	} else if (t == "energy") {
		object = new EnergyObject();
	} else if (t == "fog") {
		property = new FogProperty();
	} else if (t == "jam") {
		property = new JamProperty();
	} else {
		// invalid type
		invalidType = true;
	}
}

bool SimEntity::isProperty() {
	return property != NULL;
}

bool SimEntity::isInvalid() {
	return invalidType;
}

bool SimEntity::stopsMovableObjects() {
	// propagate it to the object
	if (object != NULL) return object->stopsMovableObjects();
	else return false;
}

int SimEntity::moveDistance() {
	// propagate it to the object
	if (object != NULL) return object->moveDistance();
	else return false;
}

int SimEntity::getType() {
	SimType r;
	if (object != NULL) r = object->getType();
	else if (property != NULL) r = property->getType();
	else r = SimTypeUndefined;

	// cast it to an int since that's what other Simulations will expect
	// i liked my enum better... =[
	return (int) r;
}


int SimEntity::setValueForProperty(string &v, string &p) {
	if (!p.length()) return 1;
	if (!v.length()) return 1;

	int propValue = atoi(v.c_str());

	// check the values needed for every object
	if (p == "type") {
		// we already know the type o.O
	} else if (p == "xloc") {
		xLoc = propValue;
	} else if (p == "yloc") {
		yLoc = propValue;
	} else if (p == "name") {
		name = v;
	} else if (p == "display") {
		display = v;
	} else {
		// both objects need to know the color
		if (p == "color") color = v;
		if (object != NULL) return object->setValueForProperty(v, p);
		else if (property != NULL) return property->setValueForProperty(v, p);
		else return 1;
	}

	return 0;
}

string SimEntity::description() {
	string s = name;

	// propagate it to the object/property
	if (object != NULL) s += object->description();
	else if (property != NULL) s += property->description();

	return s;
}

string SimEntity::configDescription() {
	string s = "";

	// we don't want any other properties, since we don't need them
	if (object != NULL) s += "<Object>\n";
	else if (property != NULL) s += "<Property>\n";

	s += "type = " + type + "\n";
	if (color.length()) s += "color = " + color + "\n";

	// this seemed to be the best way to get an int into a string
	stringstream xstream;
	xstream << xLoc;
	s += "xloc = " + xstream.str() + "\n";

	stringstream ystream;
	ystream << yLoc;
	s += "yloc = " + ystream.str() + "\n";

	s += "display = ";
	if (object != NULL) s += object->getDisplay() + "\n" + "</Object>\n";
	else if (property != NULL) s += property->getDisplay() + "\n" + "</Property>\n";

	// return the config string we created
	return s;
}

// a bunch of simple getters
string SimEntity::getName() {
	return name;
}

string SimEntity::getDisplay() {
	return display;
}


int SimEntity::getXLoc() {
	 return xLoc;
}

int SimEntity::getYLoc() {
	return yLoc;
}

IEnvObject *SimEntity::getObject() {
	return object;
}

IEnvProperty *SimEntity::getProperty() {
	return property;
}

// setters for the locations
void SimEntity::setXLoc(int x) {
	xLoc = x;
}

void SimEntity::setYLoc(int y) {
	yLoc = y;
}
