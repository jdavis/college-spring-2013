#ifndef _SIGHT
#define _SIGHT

#include "Interfaces.h"
#include "Square.h"
#include "SimEntity.h"
#include <vector>

class Sight: public ISee {
	public:
		Sight(SimEntity *robot, Square **g, int w, int h);
		~Sight();
		list<ISimObject *>& look(int f);
	private:
		int width, height;
		int x, y;
		SimDirection direction;
		Square **grid;
		int xChange(int f);
		int yChange(int f);

};

#endif
