#ifndef TURMITE_H
#define TURMITE_H

#include <fstream>
#include <vector>
#include "rule.h"
using namespace std;

class Turmite {
	
	int x, y;
	int color;
	char state;
	vector<Rule*> system;
	
	
	Turmite(int start_x, int start_y, char start_state, int start_col, vector<Rule*> rules);
	void applyRule(const Rule *r);

	Rule* selectRule();
	void draw();

public:

	static Turmite read(const char* filename);
	
	
	void simulate();
};

#endif
