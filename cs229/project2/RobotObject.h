#ifndef _ROBOT_OBJECT
#define _ROBOT_OBJECT

#include "Interfaces.h"
#include "SimEntity.h"

class RobotObject : public IEnvObject {
	public:
		RobotObject();

		// methods from IEnvObject
		int moveDistance();
		bool stopsMovableObjects();
		bool isSeeable();
		SimSquareAction objectEnteredSquare(IEnvObject *obj);
		int setValueForProperty(string &v, string &p);

		// see if we can move
		bool canMove();

		// a robots basic moves
		void moveForward();
		void turnLeft();
		void turnRight();

		// lets probe some things
		void fireProbe(int width);

		// fire! fire! fire!
		void fireBeam(int e);

		// we were hit!
		void hitByBeam(int e);
		
		// called after every action
		void rechargeEnergy();

		// getters for our ivars
		SimType getType();
		string description();
		string getDisplay();
		SimDirection getDirection();
		int getEnergy();

		// setters for our ivars
		void setStuckFor(int s);
		void setEnergy(int e);
	private:
		int direction;
		string color;
		int energy;
		int recharge;
		int moveCost;
		int turnCost;
		int probeCost;
		float paramA;
		float paramB;
		float paramC;
		int stuckFor;
};

#endif
