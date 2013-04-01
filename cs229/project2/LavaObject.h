#ifndef _LAVA_OBJECT
#define _LAVA_OBJECT

#include "Interfaces.h"
#include "SimEntity.h"

class LavaObject : public IEnvObject {
	public:
		LavaObject();
		int moveDistance();
		bool stopsMovableObjects();
		bool isSeeable();
		SimSquareAction objectEnteredSquare(IEnvObject *obj);
		int setValueForProperty(string &v, string &p);
		SimType getType();
		string description();
		string getDisplay();
	private:
		int damage;
};

#endif
