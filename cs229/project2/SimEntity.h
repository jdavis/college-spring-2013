#ifndef _SIM_ENTITY
#define _SIM_ENTITY

#include <string>
#include <list>
#include "Interfaces.h"

class SimEntity: public ISimObject {
	public:
		SimEntity(string &type);

		// a quick check to see if the SimEntity holds a property or object
		bool isProperty();
		
		// to see if the type given is known
		bool isInvalid();

		// for moving of objects
		bool stopsMovableObjects();

		// the move distance of the movable object
		int moveDistance();


		// the type the SimEntity holds
		int getType();

		// check our private variables first
		int setValueForProperty(string &v, string &p);

		// propagate the description to the object/property
		string description();
		
		// used with ./create to make things easy
		string configDescription();

		// setters for the location, only can be used by the simulation
		void setXLoc(int x);
		void setYLoc(int y);

		// getters for instance variables
		string getName();
		string getDisplay();
		int getXLoc();
		int getYLoc();
		IEnvObject *getObject();
		IEnvProperty *getProperty();
	protected:
		string name;
		string display;
		string type;
		string color;
		int xLoc, yLoc;
		bool invalidType;
		IEnvObject *object;
		IEnvProperty *property;
};

#endif
