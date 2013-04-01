#ifndef _NORMAL_PROBE
#define _NORMAL_PROBE

#include "Interfaces.h"
#include "Square.h"

class NormalProbe: public IProbe {
	public:
		NormalProbe(SimEntity *robot, Square **g, int w, int width, int height);
		~NormalProbe();
		list<ISimObject *>& probe();
	private:
		list<ISimObject *> *l;
		int x, y;
		int sWidth, sHeight;
		Square **grid;
		ISimObject *scanAlong(int x, int y, int dx, int dy);
};

#endif
