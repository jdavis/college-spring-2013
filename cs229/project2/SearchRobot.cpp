#include "Interfaces.h"
#include "SearchRobot.h"
#include <iostream>

class SearchMove : public IMove {
	public:
		SearchMove(int a, int p);
		int getAction();
		int getParameter();
	private:
		int action;
		int parameter;
};

SearchMove::SearchMove(int a, int p) {
	action = a;
	parameter = p;
}

int SearchMove::getAction() {
	return action;
}

int SearchMove::getParameter() {
	return parameter;
}

SearchRobot::SearchRobot() {
	//cout << "Creating a new SearchRobot" << endl;
	nextMoves = new list<int>;
	previousMoves = new list<int>;
	direction = 0;
	deltaX = 0;
	deltaY = 0;
	moves = 0;
	xLoc = -1;
	yLoc = -1;
	didBackTrack = false;

	map = new int*[10];
	for(int f = 0; f < 10; f++) {
		map[f] = new int[30];
		for(int j = 0; j < 30; j++) {
			map[f][j] = 0;
		}
	}
	//cout << "Finsihed creating a new SearchRobot" << endl;
}

IMove &SearchRobot::getMove(ISee & s, IProbe & p) {
	//cout << "Getting SearchRobot move" << endl;
	int action = (!moves) ? 2 : 1;
	int parameter = 0;
	int x = -1, y = -1;

	int priority[7];

	for(int f = 0; f < 7; f++) priority[f] = 0;

	//cout << "Checking things..." << endl;
	if (nextMoves->size() != 0) {
		//cout << "has next moves?? " << endl;
		action = nextMoves->front();
		nextMoves->pop_front();
		if (nextMoves->size() == 0) hasNextMoves = false;
	} else {
		//cout << "Into else " << endl;
		for(int f = 0; f < 8; f++) {
			//cout << "Sight = " << f << endl;
			list<ISimObject *> l = s.look(f);

			list<ISimObject *>::iterator it;
			ISimObject *sim;
			for(it = l.begin(); it != l.end(); it++) {
				sim = *it;
				priority[f] = levelForObject(sim);
				x = sim->getXLoc();
				y = sim->getYLoc();

				if (sim->getType() == 8) {
					cout << "Found energy pill at:" << x << ", " << y << endl;
				}

				int dy, dx;
				//cout << "If xloc == -1" << endl;
				if (xLoc == -1 && yLoc == -1) {
					dx = xChange(f);
					dy = yChange(f);

					xLoc = x + dx;
					yLoc = y + dy;
				}
			}

			if (!priority[f]) priority[f] = 1;
			
			// if we have a position, go out into the world
			if (moves == 0) {
				//cout << "If moves == 0" << endl;
				if (x >= 0 && y >= 0) {
					if (x > 5) action = 3;
					else action = 2;
				}
			} else {
				//cout << "else moves > 0" << endl;
				if (xLoc == -1 && yLoc == -1) {
					//cout << " xloc and yloc == -1 again" << endl;
					// we need to find our original position by searching around us
					if (moves < 9) {
						action = 1;
					} else if (moves > 9) {
						if (direction == 0) action = performAction(2);
						else if (direction == 1) action = performAction(2);
						else action = 1;
					} else if (moves == 9) {
						// venture out
						action = performAction(2);
					} else {
						action = performAction(1);
					}
				} else {
					////cout << "else called, going to map" << endl;
					////cout << "x = " << x << " y = " << y << endl;

					if (x != -1 && y!= -1) map[y][x] = 1;
					// mark around us where no energy pill is
					
					for(int f = 0; f < 7; f++) {
						if (priority[f] == 6) {
							moveToEp(f, priority);
						}
					}

					//cout << "priority moving stuff" << endl;
					// no energy pill and no where to move, we need to be intelligent
					// move in a direction that we can
					if (priority[0] == 1 && hasNotVisited(0)) {
						//cout << "priority0" << endl;
						action = performAction(1);
					} else if (priority[2] == 1 && hasNotVisited(2)) {
						//cout << "priority2" << endl;
						action = performAction(2);
						pushMoveForward();
					} else if (priority[6] == 1 && hasNotVisited(6)) {
						//cout << "priority6" << endl;
						action = performAction(3);
						pushMoveForward();
					} else {
						// we have already moved in all of the possible directions, 
						//cout << "back tracking" << endl;
						action = backtrack();
					}
				}
			}
		}
	}

	moves++;
	if (yLoc != -1 && xLoc != -1) {
		int dx = (direction == SimRight) - (direction == SimLeft);
		int dy = (direction == SimDown) - (direction == SimUp);

		if (action == 1) {
			if (xLoc < 30 && yLoc < 10 && xLoc > 0 && yLoc > 0) {
				xLoc += dx;
				yLoc += dy;
			}
		}

		map[yLoc][xLoc] = 1;
	}

	SearchMove *move = new SearchMove(action, parameter);
	return *move;
}

bool SearchRobot::hasNotVisited(int f) {
	int dx = xChange(f);
	int dy = yChange(f);
	
	int x = xLoc + dx;
	int y = yLoc + dy;

	//cout << "Current location = " << xLoc << ", " << yLoc << endl;

	if (x < 5 || x >= 20) return false;
	if (y < 5 || y >= 10) return false;

	//cout << "Checking " << x << ", " << y << endl;
	return map[y][x];
}

int SearchRobot::backtrack() {
	int r;
	
	// keep back tracking
	if (didBackTrack) {
		//cout << "did backtrack" << endl;
		if (previousMoves->size() != 0) {
			r = previousMoves->back();
			previousMoves->pop_back();
		}
	} else {
		// we need to turn around first
		//cout << "turn around first" << endl;
		pushTurnLeft();
		r = performAction(3);
	}
	
	// let us know in the future if we have to turn around
	didBackTrack = true;
	return r;
}

// ugly code
int SearchRobot::xChange(int f) {
	int dx;

	// since the direction changes, we need to take that into consideration
	// there probably is a few line algorithm for this, but i'm a little pressed for time
	if (direction == 0) {
		if (f == 7 || f == 6 || f == 5) dx = -1;
		else if (f == 1 || f == 2 || f == 3) dx = 1;
		else dx = 0;
	} else if (direction == 1) {
		if (f == 7 || f == 0 || f == 1) dx = 1;
		else if (f == 5 || f == 4 || f == 3) dx = -1;
		else dx = 0;
	} else if (direction == 2) {
		if (f == 7 || f == 6 || f == 5) dx = 1;
		else if (f == 1 || f == 2 || f == 3) dx = -1;
		else dx = 0;
	} else if (direction == 3) {
		if (f == 7 || f == 0 || f == 1) dx = -1;
		else if (f == 5 || f == 4 || f == 3) dx = 1;
		else dx = 0;
	}

	return dx;
}

int SearchRobot::yChange(int f) {
	int dy;

	// since the direction changes, we need to take that into consideration
	// there probably is a few line algorithm for this, but i'm a little pressed for time
	if (direction == 0) {
		if (f == 7 || f == 0 || f == 1) dy = -1;
		else if (f == 5 || f == 4 || f == 3) dy = 1;
		else dy = 0;
	} else if (direction == 1) {
		if (f == 7 || f == 6 || f == 5) dy = -1;
		else if (f == 1 || f == 2 || f == 3) dy = 1;
		else dy = 0;
	} else if (direction == 2) {
		if (f == 7 || f == 0 || f == 1) dy = 1;
		else if (f == 5 || f == 4 || f == 3) dy = -1;
		else dy = 0;
	} else if (direction == 3) {
		if (f == 7 || f == 6 || f == 5) dy = 1;
		else if (f == 1 || f == 2 || f == 3) dy = -1;
		else dy = 0;
	}

	return dy;
}

int SearchRobot::levelForObject(ISimObject *s) {
	int p = 0;
	switch(s->getType()) {
		case 10:
			p = 1;
			break;
		case 3:
		case 4:
			p = 2;
			break;
		case 0:
		case 5:
		case 6:
			p = 3;
		case 1:
		case 2:
		case 7:
			p = 4;
		case 9:
			p = 5;
		case 8:
			p = 6;
	}

	return p;
}

void SearchRobot::moveToEp(int f, int *priority) {
	int canMoveRight = (priority[2] < 4);
	int canMoveLeft = (priority[6] < 4);
	int canMoveUp = (priority[0] < 4);
	int canMoveDown = (priority[4] < 4);

	if (f == 0) {
		pushMoveForward();
	} else if (f == 1) {
		if (canMoveUp) {
			pushMoveForward();
			pushTurnRight();
			pushMoveForward();
		} else if (canMoveRight) {
			pushTurnRight();
			pushMoveForward();
			pushTurnLeft();
			pushMoveForward();
		} else {
			return;
		}
	} else if (f == 2) {
		pushTurnRight();
		pushMoveForward();
	} else if (f == 3) {
		if (canMoveRight) {
			pushTurnRight();
			pushMoveForward();
			pushTurnRight();
			pushMoveForward();
		} else if (canMoveDown) {
			pushTurnRight();
			pushTurnRight();
			pushMoveForward();
			pushMoveForward();
			pushTurnLeft();
			pushMoveForward();
		}
	} else if (f == 4) {
		pushTurnRight();
		pushTurnRight();
		pushMoveForward();
	} else if (f == 5) {
		if (canMoveLeft) {
			pushTurnLeft();
			pushMoveForward();
			pushTurnLeft();
			pushMoveForward();
		} else if (canMoveDown) {
			pushTurnRight();
			pushTurnRight();
			pushMoveForward();
			pushTurnRight();
			pushMoveForward();
		}
	} else if (f == 6) {
		pushTurnLeft();
		pushMoveForward();
	} else if (f == 7) {
		if (canMoveUp) {
			pushMoveForward();
			pushTurnLeft();
			pushMoveForward();
		} else if (canMoveLeft) {
			pushTurnLeft();
			pushMoveForward();
			pushTurnRight();
			pushMoveForward();
		}
	}
}

int SearchRobot::performAction(int a) {
	didBackTrack = false;
	if (a == 1) {
		int xm = (direction == 1) - (direction == 3);
		int ym = (direction == 0) - (direction == 2);

		xLoc += xm;
		yLoc += ym;
		map[yLoc][xLoc] = true;
	} else if (a == 2) {
		direction = (direction + 1) % 4;
	} else if (a == 3) {
		direction = (direction - 1) % 4;
	}

	return a;
}

void SearchRobot::pushMoveForward() {
	nextMoves->push_back(1);
	previousMoves->push_back(1);
}

void SearchRobot::pushTurnRight() {
	nextMoves->push_back(2);
	previousMoves->push_back(3);
}

void SearchRobot::pushTurnLeft() {
	nextMoves->push_back(3);
	previousMoves->push_back(2);
}
