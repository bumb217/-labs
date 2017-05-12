//
//  Turmite.hpp
//  laba-3(turmite)
//
//  Created by Андрей Пригода on 25.04.17.
//  Copyright © 2017 Андрей Пригода. All rights reserved.
//

#ifndef Turmite_h
#define Turmite_h

#include <stdio.h>
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
//    void draw();
    
public:
    
    static Turmite read(const char* filename);
    
    void draw();
    
    void simulate();
};
#endif /* Turmite_h */
