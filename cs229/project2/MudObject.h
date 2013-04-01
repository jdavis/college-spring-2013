#ifndef _MUD_OBJECT
#define _MUD_OBJECT

#include "Interfaces.h"
#include "SimEntity.h"

class MudObject : public IEnvObject {
	public:
		MudObject();
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
		int delay;
};

#endif
