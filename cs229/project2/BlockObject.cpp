#include <iostream>
#include "BlockObject.h"

// default color is blue for blocks
BlockObject::BlockObject() {
	color = "blue";
}

int BlockObject::moveDistance() {
	return 1;
}

bool BlockObject::stopsMovableObjects() {
	return true;
}

bool BlockObject::isSeeable() {
	return true;
}

SimSquareAction BlockObject::objectEnteredSquare(IEnvObject *obj) {
	if (obj->getType() == SimTypeRobot)
		return SimMoveEntity;
	else return SimDoNothing;
}

// we only have the color to worry about
int BlockObject::setValueForProperty(string &v, string &p) {
	if (!p.length()) return 1;
	if (!v.length()) return 1;
	if (p == "color") color = v;
	else return 1;

	return 0;
}

SimType BlockObject::getType() {
	return SimTypeBlock;
}

string BlockObject::description() {
	return "\nColor " + color;
}

string BlockObject::getDisplay() {
	string disp = "";
	if (color.size()) disp.push_back(toupper(color[0]));
	disp.push_back('B');
	return disp;
}
