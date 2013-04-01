#ifndef _BALL_OBJECT
#define _BALL_OBJECT

#include "Interfaces.h"
#include "SimEntity.h"

class BallObject : public IEnvObject {
	public:
		BallObject();
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
