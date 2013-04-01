#ifndef _ROCK_OBJECT
#define _ROCK_OBJECT

#include "Interfaces.h"
#include "SimEntity.h"

class RockObject : public IEnvObject {
	public:
		int moveDistance();
		bool stopsMovableObjects();
		bool isSeeable();
		SimSquareAction objectEnteredSquare(IEnvObject *obj);
		int setValueForProperty(string &v, string &p);
		SimType getType();
		string description();
		string getDisplay();
};

#endif
