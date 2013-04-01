#ifndef _SIM_INTERFACES
#define _SIM_INTERFACES

#include <cstdlib>
#include <string>
#include <list>

using namespace std;

// some enums so we don't have to memorize the numbers for everything
enum SimType {
	SimTypeUndefined = -1,
	SimTypeRobot = 0,
	SimTypeRock, 		// 1
	SimTypeLava, 		// 2
	SimTypeWater, 		// 3
	SimTypeMud, 		// 4
	SimTypeBall, 		// 5
	SimTypeBlock, 		// 6
	SimTypeHole, 		// 7
	SimTypeEnergyPill, 	// 8
	SimTypeFog, 		// 9
	SimTypeJam, 		// 10
	SimTypeFirst = SimTypeRobot,
	SimTypeLast = SimTypeJam
};

enum SimDirection {
	SimUp = 0,
	SimRight,
	SimDown,
	SimLeft
};

// returned by the square when an object moves into it
enum SimSquareAction {
	SimDoNothing = 0,
	SimRemoveEntity,
	SimRemoveSelf,
	SimMoveEntity
};

// the .getAction() of an IMove
enum SimRobotAction {
	SimRobotStay = 0,
	SimRobotForward,
	SimRobotTurnRight,
	SimRobotTurnLeft,
	SimRobotProbe,
	SimRobotPulse
};

// the core class for every object in the sim
class ISimObject {
	public:
		virtual string getName() = 0;
		virtual string getDisplay() = 0;
		virtual int getXLoc() = 0;
		virtual int getYLoc() = 0;
		virtual int getType() = 0;
};

class ISee {
	public:
		virtual list<ISimObject *>& look(int x) = 0;
};

class IProbe {
	public:
		virtual list<ISimObject *>& probe() = 0;
};

class IMove {
	public:
		virtual int getAction() = 0;
		virtual int getParameter() = 0;
};

class IRobot {
	public:
		virtual IMove & getMove(ISee & s, IProbe & p) = 0;
};

class ISimulation {
	public:
		virtual void loadConfiguration(string file) = 0;
		virtual void setRobot(int index, IRobot & r) = 0;
		virtual void step(int s) = 0;
};

// the class that represents an actual object on the grid
// objects all have the characteristic that they affect other objects if one enters it
class IEnvObject {
	public:
		// basically a 1 or 0 if they can move
		virtual int moveDistance() = 0;

		// blocks and balls all stop moveable objects
		virtual bool stopsMovableObjects() = 0;

		// for use with the probe
		virtual bool isSeeable() = 0;

		// the action to do when an object enters the same square
		virtual SimSquareAction objectEnteredSquare(IEnvObject *obj) = 0;

		// kind of like key value programming in ObjC, it works quite well
		// it returns a 1 if the property isn't valid for that class
		virtual int setValueForProperty(string &v, string &p) = 0;

		// each object has a different type
		virtual SimType getType() = 0;

		// to print out descriptions and what not
		virtual string getDisplay() = 0;

		// a description for the output of the simulation
		virtual string description() = 0;
};

// the class to represent properties such as fog and jam
// properties all have the characteristic that they affect when
// either the robot tries to probe or see
class IEnvProperty {
	public:
		// distinguish between one that affects the probe or sight
		virtual bool affectsProbe() = 0;
		virtual bool affectsSight() = 0;
		
		// corresponding method to get the new sight/probe
		virtual ISee *propertySight() = 0;
		virtual IProbe *propertyProbe() = 0;

		// some more key value programming
		virtual int setValueForProperty(string &v, string &p) = 0;

		// each property has a differnet type
		virtual SimType getType() = 0;

		// to print out descriptions again
		virtual string getDisplay() = 0;

		// ouput for the simulation
		virtual string description() = 0;
};

#endif
