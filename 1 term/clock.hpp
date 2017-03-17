//
//  clock.hpp
//  laba-4
//
//  Created by Андрей Пригода on 24.01.17.
//  Copyright © 2017 Андрей Пригода. All rights reserved.
//

#ifndef clock_hpp
#define clock_hpp

#include <stdio.h>
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <OpenGL/gl3.h>

void display();
void specialKeys(int key, int x, int y);

class Clock
{
public:
    
    double rotate_y;
    double rotate_x;
    
    Clock()
    {
        rotate_x = 0;
        rotate_y = 0;
        a.x[0] = 0.05; a.x[1] = -0.05; a.x[2] = 0.0;
        a.y[0] = 0;    a.y[1] = 0.0;   a.y[2] = 0.2;
        b.x[0] = 0.05; b.x[1] = -0.05; b.x[2] = 0.0;
        b.y[0] = 0.0;  b.y[1] = 0.0;   b.y[2] = 0.3;
        c.x[0] = 0.02; c.x[1] = -0.02; c.x[2] = 0.0;
        c.y[0] = 0.0;  c.y[1] = 0.0;   c.y[2] = 0.35;
    };
    
    struct triangle
    {
        double x[3], y[3];
    } a, b, c;
    
    double Calc_Sec(int iSec);
    double Calc_Min(int iMin, int iSec);
    double Calc_Hr(int iHr, int iMin, int iSec);
    void drawCircle();
    void drawCube();
    void drawNumbers();
    void drawArrays();
    void drawLines();
};
#endif /* clock_hpp */
