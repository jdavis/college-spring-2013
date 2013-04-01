#ifndef _WATER_OBJECT
#define _WATER_OBJECT

#include "Interfaces.h"
#include "SimEntity.h"

class WaterObject : public IEnvObject {
	public:
		WaterObject();
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
