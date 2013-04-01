#ifndef _BLOCK_OBJECT
#define _BLOCK_OBJECT

#include "Interfaces.h"
#include "SimEntity.h"

class BlockObject : public IEnvObject {
	public:
		BlockObject();
		int moveDistance();
		bool stopsMovableObjects();
		bool isSeeable();
		SimSquareAction objectEnteredSquare(IEnvObject *obj);
		int setValueForProperty(string &v, string &p);
		SimType getType();
		string description();
		string getDisplay();
	private:
		string color;
};

#endif
