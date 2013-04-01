#include <iostream>
#include "EnergyPill.h"

int EnergyPill::getType() {
	return SOEnergyPill;
}

int EnergyPill::setPropForValue(string &p, string &v) {
	if (!p.length()) return 1;
	//int propValue = intFromProp(v);
	//cout << p + " = " + v << endl;
	int propValue = atoi(v.c_str());
	string *n = new string(v);

	if (p == "xloc") {
		xloc = propValue;
	} else if (p == "yloc") {
		yloc = propValue;
	} else if (p == "name") {
		name = n;
	} else if (p == "display") {
		display = n;
	}

	return 1;
}
