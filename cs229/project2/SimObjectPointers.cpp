
#include <iostream>
#include <fstream>
#include <string>
#include <ctype.h>
#include "Includes.h"
#include "Simulation.h"

Simulation::Simulation() {
	width = 0;
	height = 0;
	steps = 0;
}

void Simulation::loadConfiguration(string file) {
	ifstream f(file.c_str());
	string line;

	bool inElement = 0;
	list<SimObject *> objects;
	SimObject *obj = 0;
	string name;
	while(f.good()) {
		getline(f, line);
		
		if (!line.length()) continue;
		
		//cout << line << endl;
		name = findElementName(line);

		if (name.length()) {
			// check the name
			inElement = !(name[0] == '/');

			if (!inElement) continue;
		}
		
		//cout << "In element " << inElement << endl;
		
		if (inElement) {
			//cout << name << endl;
			list<string *> r;
			r = findPropAndValue(line);
			list<string *>::iterator it = r.begin();
			string *key = *(it++);
			string *value = *(it++);

			//cout << key + " = " << endl;

			if (*key == "width")
				width = atoi(value->c_str());
			if (*key == "height")
				height = atoi(value->c_str());
			if (*key == "steps")
				steps = atoi(value->c_str());

			if (*key == "type") {
				//cout << "New type " + value << endl;
				if (obj) {
					objects.push_back(obj);
					//cout << obj->getName() << endl;
				}
				obj = objectForType(*value);
				//cout << "Obj name = " << obj->getDisplay() << endl;
			}

			//cout << value << endl;

			//if (obj != NULL) obj->setPropForValue(key, value);

			//cout << "Name= " + key + " Value = " + value << endl;
		} else {
			cout << "not in element" << endl;
		}
	}

	list<SimObject *>::iterator it = objects.begin();
	for(it = objects.begin(); it != objects.end(); it++) {
		//cout << *it << endl;
		//SimObject *obj = *it;
		//cout << obj->getName() << endl;
	}
}

// extracts the element within <>
// it returns a blank string if it doesn't find one
// or if the format isn't correct
string Simulation::findElementName(string l) {
	bool inBrackets = 0;
	unsigned int f;
	string name;
	for(f = 0; f < l.length(); f++) {
		char c = tolower(l[f]);

		if (c == '<') {
			if (inBrackets) return "";

			inBrackets = 1;
		} else if (c == '>') {
			if (!inBrackets) return "";
			inBrackets = 0;
			break;
		} else if (inBrackets) {
			name.push_back(c);
		}
	}
	
	if (inBrackets) return "";

	return name;
}

list<string *> Simulation::findPropAndValue(string &l) {
	list<string *> lst;

	size_t f;
	string *name;
	string *value;
	size_t comment = l.find("//");
	//cout << "comment at " << comment << endl;
	size_t equals = l.find("=");

	if (equals == string::npos) return lst;

	int words = 0;
	bool newWord = 0;
	for(f = 0; f < l.length(); f++) {
		char c = l[f];

		if (c == '=') {
			continue;
		} else if (f == comment){
			break;
		} else if (words == 1 || !isspace(c)) {
			newWord = 1;
			if (words == 0) {
				name->push_back(c);
			} else if (words == 1) {
				if (isspace(c) && value->length() == 0) continue;
				value->push_back(c);
			}
		} else {
			if (newWord) {
				words++;
				newWord = 0;
			}
		}
	}

	//cout << "words = " << words << endl;
	cout << "name = " << name << endl;
	cout << "value = " << value << endl;

	//for(f = 0; f < lst.size(); f++) {
		//cout << lst[f] << endl;
	//}
	
	// we found more words than what we wanted
	if (words > 2) return lst;

	// bad name
	if (name->length() == 0) return lst;

	// bad value
	if (value->length() == 0) return lst;

	//cout << "pushing name and value" << endl;
	lst.push_back(trim(name));
	lst.push_back(trim(value));

	return lst;
}

/*
void Simulation::setRobot(int index, IRobot robo) {

}
*/

void Simulation::step(int s) {

}

SimObject *Simulation::objectForType(string t) {
	SimObject *o;
	o = new Robot();
	/*
	if (t == "robot") {
		o = new Robot();
	} else if (t == "rock") {
		o = new Rock();
	} else if (t == "lava") {
		o = new Lava();
	} else if (t == "water") {
		o = new Water();
	} else if (t == "mud") {
		o = new Mud();
	} else if (t == "ball") {
		o = new Ball();
	} else if (t == "block") {
		o = new Block();
	} else if (t == "hole") {
		o = new Hole();
	} else if (t == "energy") {
		o = new EnergyPill();
	} else if (t == "fog") {
		o = new Fog();
	} else if (t == "jam") {
		o = new Jam();
	} else {
		cout << "else for type " + t << endl;
		return 0;
	}
	*/


	cout << "Obj name = " + o->getName() << endl;
	return o;
}

string Simulation::trim(string s) {
	size_t end = s.find_last_not_of(" \r\n\t");
	if (end != string::npos) return s.substr(0, end + 1);
	else return s;
}
