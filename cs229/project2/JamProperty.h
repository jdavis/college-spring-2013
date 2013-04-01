#ifndef _JAM_PROPETY
#define _JAM_PROPETY

#include "Interfaces.h"
#include "SimEntity.h"

class JamProperty : public IEnvProperty {
	public:
		bool affectsProbe();
		bool affectsSight();
		ISee *propertySight();
		IProbe *propertyProbe();
		int setValueForProperty(string &v, string &p);
		SimType getType();
		string getDisplay();
		string description();
};

#endif
