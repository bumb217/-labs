//
//  Turmite.cpp
//  laba-3(turmite)
//
//  Created by Андрей Пригода on 25.04.17.
//  Copyright © 2017 Андрей Пригода. All rights reserved.
//

#include "Turmite.h"
#include "rule.h"
#include "painter.h"

#include <iostream>

const int sz = 15;

Turmite::Turmite(int x, int y, char state, int col, vector<Rule*> rules) {
    system = rules;
    this->color = col;
    
    this->state = state;
    this->x = x;
    this->y = y;
}

void Turmite::applyRule(const Rule *r) {
    state = r->new_state;
    color = r->new_col;
    
    switch(r->direction) {
        case North: y -= sz; break;
        case East:  x += sz; break;
        case South: y += sz; break;
        case West:  x -= sz; break;
    }
}
void Turmite::draw() {
    if (color == -1) return;
//    glBegin(GL_POINTS);

    
    drawMite(x, y, sz, color);
//    glEnd();


}
Rule* Turmite::selectRule() {
    for (int i = 0; i < system.size(); i++) {
        Rule *r = system.at(i);
        if ((r->cur_col == color) && (r->cur_state == state)) {
            return r;
        }
    }
    
    return NULL;
}

Turmite Turmite::read(const char *filename) {
    ifstream in(filename);
    
    int x, y, col; char state;
    in >> x >> y >> state >> col;
    
    vector<Rule*> rules;
    int n; in >> n;
    for (int i = 0; i < n; i++) {
        rules.push_back(Rule::read(in));
    }
    
    return Turmite(x, y, state, col, rules);
}

void Turmite::simulate() {
    Rule *rule;
    draw();
//    std::system("Pause");
    
    while (rule = selectRule()) {
        applyRule(rule);
        
        if (x < sz || y < sz || x > 300 || y > 300) {
//            std::system("cls");
            glClear(GLUT_DOUBLE);
            cout << "Field bounds reached!" << endl;
//            std::system("Pause");
            return;
        }
        else {
            draw();
//            std::system("cls");
//            std::system("Pause");
            glClear(GLUT_DOUBLE);

        }
    }
    
}
