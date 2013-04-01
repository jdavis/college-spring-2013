#ifndef _SIM_SQUARE
#define _SIM_SQUARE

#include <string>
#include <vector>
#include <list>
#include "Interfaces.h"
#include "SimEntity.h"

class Square {
	public:
		Square();
		// quick way to check if there are objects or properties
		int getSize();

		// used to see if an object can be placed in a square
		bool canPlaceObjectWithMask(SimEntity &e, int mask);

		// determines if objects can be moved
		bool acceptsMovableObjects();
		bool canMoveInto();
		
		// methods for determining if we should alter the probe or sight
		bool affectsSight();
		ISee *sight();
		bool affectsProbe();
		IProbe *probe();

		// there should only be one object that is movable in a square
		SimEntity *entityToMove();
		
		// add the entity to the square and return the action
		SimSquareAction addEntity(SimEntity *e);

		// remove the entity from the square
		// used for moving objects as well as destroying them
		void removeEntity(SimEntity *e);

		// used to iterate through all of the objects
		list<SimEntity *> *allEntities();

		// methods for printing things back to the user
		string shortDescription();
		string longDescription();
		string configDescription();
	private:
		// the objects in the square
		list<SimEntity *> *entities;
		
		// the properties in the square
		list<SimEntity *> *properties;
};
#endif
