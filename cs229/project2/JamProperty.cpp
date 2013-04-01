#include <iostream>
#include "Interfaces.h"
#include "JamProperty.h"

// an inner class that is basically a failed probe, nothing is returned
class JamProbe : public IProbe {
	public:
		JamProbe();
		~JamProbe();
		list<ISimObject *>& probe();
	private:
		list<ISimObject *> *p;
};

JamProbe::JamProbe() {
	p = new list<ISimObject *>;
}

JamProbe::~JamProbe() {
	delete p;
}

bool JamProperty::affectsProbe() {
	return true;
}

bool JamProperty::affectsSight() {
	return false;
}

list<ISimObject *>& JamProbe::probe() {
	return *p;
}

ISee *JamProperty::propertySight() {
	return NULL;
}

// return the empty probe
IProbe *JamProperty::propertyProbe() {
	return new JamProbe();
}

int JamProperty::setValueForProperty(string &v, string &p) {
	return 1;
}

SimType JamProperty::getType() {
	return SimTypeJam;
}

string JamProperty::getDisplay() {
	return "J";
}

string JamProperty::description() {
	return "";
}
