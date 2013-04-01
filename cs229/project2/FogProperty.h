#ifndef _FOG_PROPERTY
#define _FOG_PROPERTY

#include "Interfaces.h"
#include "SimEntity.h"

class FogProperty : public IEnvProperty {
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
