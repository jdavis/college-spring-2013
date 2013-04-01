#include <iostream>
#include "Interfaces.h"
#include "FogProperty.h"

// inner class that returns nothing for the sight
class FogSight : public ISee {
	public:
		FogSight();
		~FogSight();
		list<ISimObject *>& look(int x);
	private:
		list<ISimObject *> *sight;
};

FogSight::FogSight() {
	sight = new list<ISimObject *>;
}

FogSight::~FogSight() {
	delete sight;
}

bool FogProperty::affectsProbe() {
	return false;
}

bool FogProperty::affectsSight() {
	return true;
}

// our robot can't see anything so pass that
list<ISimObject *>& FogSight::look(int x) {
	return *sight;
}

ISee *FogProperty::propertySight() {
	return new FogSight();
}

IProbe *FogProperty::propertyProbe() {
	return NULL;
}

int FogProperty::setValueForProperty(string &v, string &p) {
	return 1;
}

SimType FogProperty::getType() {
	return SimTypeFog;
}

string FogProperty::getDisplay() {
	return "F";
}

string FogProperty::description() {
	return "";
}
