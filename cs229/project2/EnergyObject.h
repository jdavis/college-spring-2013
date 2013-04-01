#ifndef _ENERGY_OBJECT
#define _ENERGY_OBJECT

#include "Interfaces.h"
#include "SimEntity.h"

class EnergyObject : public IEnvObject {
	public:
		EnergyObject();
		int moveDistance();
		bool stopsMovableObjects();
		bool isSeeable();
		SimSquareAction objectEnteredSquare(IEnvObject *obj);
		int setValueForProperty(string &v, string &p);
		SimType getType();
		string description();
		string getDisplay();
	private:
		int energy;
};

#endif
