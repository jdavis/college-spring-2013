#ifndef _EMPTY_PROBE
#define _EMPTY_PROBE

#include "Interfaces.h"

class EmptyProbe : public IProbe {
	public:
		list<ISimObject *>& probe();
};

#endif
