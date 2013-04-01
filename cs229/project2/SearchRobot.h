#ifndef _SIGHT
#define _SIGHT

#include "Interfaces.h"

class SearchRobot : public IRobot {
	public:
		SearchRobot();
		IMove &getMove(ISee & s, IProbe & p);
	private:
		int xLoc, yLoc;
		int moves;
		int **map;
		int direction;
		int deltaX;
		int deltaY;
		bool hasNextMoves;
		bool didBackTrack;
		list<int> *nextMoves;
		list<int> *previousMoves;
		int levelForObject(ISimObject *s);
		void pushMoveForward();
		void pushTurnRight();
		void pushTurnLeft();
		int xChange(int f);
		int yChange(int f);
		void moveToEp(int f, int *priority);
		int performAction(int a);
		void markMap();
		bool hasNotVisited(int f);
		// to go back in the direction we came
		int backtrack();
};

#endif
