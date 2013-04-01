#include "Square.h"
#include "Sight.h"
#include <iostream>

Square::Square() {
	// set up our stuff, yo
	entities = new list<SimEntity *>;
	properties = new list<SimEntity *>;
}

int Square::getSize() {
	return entities->size() + properties->size();
}

bool Square::affectsSight() {
	list<SimEntity *>::iterator it;

	// check to see if the properties in the square alter the sight
	if (properties->size()) {
		for(it = properties->begin(); it != properties->end(); it++) {
			IEnvProperty *ent = (*it)->getProperty();
			if (ent->affectsSight()) return true;
		}
	}

	return false;
}

ISee *Square::sight() {
	list<SimEntity *>::iterator it;

	// return the new sight if the property in the square affects it
	if (properties->size()) {
		for(it = properties->begin(); it != properties->end(); it++) {
			IEnvProperty *ent = (*it)->getProperty();
			if (ent->affectsSight()) return ent->propertySight();
		}
	}

	return NULL;
}

bool Square::affectsProbe() {
	list<SimEntity *>::iterator it;

	// check to see if the properties int he square alter the probe
	if (properties->size()) {
		for(it = properties->begin(); it != properties->end(); it++) {
			IEnvProperty *ent = (*it)->getProperty();
			if (ent->affectsProbe()) return true;
		}
	}

	return false;
}

IProbe *Square::probe() {
	list<SimEntity *>::iterator it;

	// return the new probe if the property in the square affects it
	if (properties->size()) {
		for(it = properties->begin(); it != properties->end(); it++) {
			IEnvProperty *ent = (*it)->getProperty();
			if (ent->affectsProbe()) return ent->propertyProbe();
		}
	}

	return NULL;
}

bool Square::canPlaceObjectWithMask(SimEntity &e, int mask) {
	list<SimEntity *>::iterator it;

	// only check objects, we dont' care about properties
	if (!e.isProperty()) {
		for(it = entities->begin(); it != entities->end(); it++) {
			SimEntity *ent = *it;

			if (!((1 << ent->getType()) & mask)) {
				return false;
			}
		}
	}

	// multiple fog properties can go into the same square
	// we could error but they don't cause any trouble if they stack
	return true;
}

SimEntity *Square::entityToMove() {
	list<SimEntity *>::iterator it;

	// first entity that is moveable
	for(it = entities->begin(); it != entities->end(); it++ ) {
		SimEntity *ent = *it;
		if (ent->moveDistance()) return ent;
	}

	return NULL;
}

bool Square::acceptsMovableObjects() {
	list<SimEntity *>::iterator it;

	for(it = entities->begin(); it != entities->end(); it++) {
		SimEntity *ent = *it;
		if (!ent->moveDistance() && ent->stopsMovableObjects()) {
			return false;
		}
	}

	return true;
}

bool Square::canMoveInto() {
	list<SimEntity *>::iterator it;

	// only return false if an object stops moveable objects
	for(it = entities->begin(); it != entities->end(); it++) {
		SimEntity *ent = *it;
		if (ent->stopsMovableObjects()) {
			return false;
		}
	}

	return true;
}

SimSquareAction Square::addEntity(SimEntity *e) {
	list<SimEntity *>::iterator it;

	SimSquareAction a = SimDoNothing;

	// look through all of the properties and see if they alter any objects
	// like a hole should return SimRemoveEntity
	for(it = entities->begin(); it != entities->end(); it++) {
		SimEntity *ent = *it;
		SimSquareAction tempAct = ent->getObject()->objectEnteredSquare(e->getObject());
		if (tempAct != SimDoNothing) {
			a = tempAct;
		}
	}

	if (!e->isProperty()) entities->push_back(e);
	else properties->push_back(e);
	
	return a;
}

void Square::removeEntity(SimEntity *e) {
	// get outta here
	entities->remove(e);
}

string Square::shortDescription() {
	string s;

	// used for the printing of the grid

	// no objects, we need periods
	if (entities->size() == 0) {
		s = "..";
	} else if (entities->size() == 1) {
		s = (entities->front())->getDisplay();
		if (s.length() == 1) s += ".";
	} else {
		// too many to show
		s = "XX";
	}

	if (properties->size() == 0) s += ".";
	else if (properties->size() == 1) s += (properties->front())->getDisplay();
	else s += "X";

	return s;
}

string Square::longDescription() {
	string s;
	list<SimEntity *>::iterator it;

	// concatenate the longer description if needed for each object/property
	for(it = entities->begin(); it != entities->end(); it++) {
		SimEntity *ent = *it;
		s += ent->description();
	}

	for(it = properties->begin(); it != properties->end(); it++) {
		SimEntity *ent = *it;
		s += ent->description();
	}

	return s;
}

string Square::configDescription() {
	string s;
	list<SimEntity *>::iterator it;

	// since each object/property handles its own, it's quite easy
	for(it = entities->begin(); it != entities->end(); it++) {
		SimEntity *ent = *it;
		s += ent->configDescription();
		if (s.length()) s += "\n";
	}

	for(it = properties->begin(); it != properties->end(); it++) {
		SimEntity *ent = *it;
		s += ent->configDescription() + "\n";
	}

	return s;
}

list<SimEntity *> *Square::allEntities() {
	return entities;
}
