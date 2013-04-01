#include "EmptyProbe.h"
#include <iostream>

// nothing to probe!
list<ISimObject *>& EmptyProbe::probe() {
	list<ISimObject *> l;
	return *(new list<ISimObject *>);
}
