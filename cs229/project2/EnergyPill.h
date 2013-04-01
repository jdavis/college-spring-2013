#include "Interfaces.h"
#include "SimObject.h"

class EnergyPill : public SimObject {
	public:
		int getType();
		int setPropForValue(string &p, string &v);
};
