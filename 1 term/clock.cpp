//
//  clock.cpp
//  laba-4
//
//  Created by Андрей Пригода on 24.01.17.
//  Copyright © 2017 Андрей Пригода. All rights reserved.
//

#include "clock.hpp"

#include <stdio.h>
#include <math.h>
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <OpenGL/gl3.h>
#include <iostream>
#include <ctime>

using namespace std;

Clock task;

double Clock::Calc_Sec(int iSec)
{
    return  (iSec * 6.0f);
}

double Clock::Calc_Min(int iMin, int iSec)
{
    return  ((iMin * 6.0f) + (Clock::Calc_Sec(iSec) / 60.0f));
}

double Clock::Calc_Hr(int iHr, int iMin, int iSec)
{
    return  ((iHr * 30.0f) + (Clock::Calc_Min(iMin, iSec) / 12.0f));
}

void Clock::drawCircle()
{
    glLineWidth(2.0);
    glBegin(GL_POLYGON);
    glColor3f(0, 0, 0);
    for (int i = 0; i < 256; i++)
    {
        double angle = 2 * 3.14159265 * i / 256;
        glVertex3f(0.05*cos(angle), 0.05*sin(angle), -0.515);
    }
    glEnd();
}

void Clock::drawCube()
{
    //Multi-colored side - FRONT
    glBegin(GL_POLYGON);
    
    glColor3f(1.0, 0.0, 0.0);     glVertex3f(0.5, -0.5, -0.5);      // P1 is red
    glColor3f(0.0, 1.0, 0.0);     glVertex3f(0.5, 0.5, -0.5);      // P2 is green
    glColor3f(0.0, 0.0, 1.0);     glVertex3f(-0.5, 0.5, -0.5);      // P3 is blue
    glColor3f(1.0, 0.0, 1.0);     glVertex3f(-0.5, -0.5, -0.5);      // P4 is purple
    
    glEnd();
    
    // White side - BACK
    glBegin(GL_POLYGON);
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(0.5, -0.5, 0.5);
    glVertex3f(0.5, 0.5, 0.5);
    glVertex3f(-0.5, 0.5, 0.5);
    glVertex3f(-0.5, -0.5, 0.5);
    glEnd();
    
    // Purple side - RIGHT
    glBegin(GL_POLYGON);
    glColor3f(1.0, 0.0, 1.0);
    glVertex3f(0.5, -0.5, -0.5);
    glVertex3f(0.5, 0.5, -0.5);
    glVertex3f(0.5, 0.5, 0.5);
    glVertex3f(0.5, -0.5, 0.5);
    glEnd();
    
    // Green side - LEFT
    glBegin(GL_POLYGON);
    glColor3f(0.0, 1.0, 0.0);
    glVertex3f(-0.5, -0.5, 0.5);
    glVertex3f(-0.5, 0.5, 0.5);
    glVertex3f(-0.5, 0.5, -0.5);
    glVertex3f(-0.5, -0.5, -0.5);
    glEnd();
    
    // Blue side - TOP
    glBegin(GL_POLYGON);
    glColor3f(0.0, 0.0, 1.0);
    glVertex3f(0.5, 0.5, 0.5);
    glVertex3f(0.5, 0.5, -0.5);
    glVertex3f(-0.5, 0.5, -0.5);
    glVertex3f(-0.5, 0.5, 0.5);
    glEnd();
    
    // Red side - BOTTOM
    glBegin(GL_POLYGON);
    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(0.5, -0.5, -0.5);
    glVertex3f(0.5, -0.5, 0.5);
    glVertex3f(-0.5, -0.5, 0.5);
    glVertex3f(-0.5, -0.5, -0.5);
    glEnd();
}

void Clock::drawArrays()
{
    /*Getting time*/
    time_t currentTime;
    struct tm *localTime;
    
    time(&currentTime);
    localTime = localtime(&currentTime);
    
    int hours = localTime->tm_hour, minutes = localTime->tm_min, seconds = localTime->tm_sec;
    hours %= 12;
    
    double angleInRad = Calc_Hr(hours, minutes, seconds) * 3.14159265 / 180.;
    triangle f = a;
    for (int i = 0; i < 3; i++)
    {
        double buffX = a.x[i], buffY = a.y[i];
        a.x[i] = buffX*cos(angleInRad) + buffY*sin(angleInRad);
        a.y[i] = -buffX*sin(angleInRad) + buffY*cos(angleInRad);
    }
    
    // hour arrow
    glBegin(GL_POLYGON);
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(a.x[0], a.y[0], -0.512);
    glVertex3f(a.x[1], a.y[1], -0.512);
    glVertex3f(a.x[2], a.y[2], -0.512);
    glEnd();
    a = f;
    
    angleInRad = Calc_Min(minutes, seconds) * 3.14159265 / 180.;
    
    f = b;
    for (int i = 0; i < 3; i++)
    {
        double buffX = b.x[i], buffY = b.y[i];
        b.x[i] = buffX*cos(angleInRad) + buffY*sin(angleInRad);
        b.y[i] = -buffX*sin(angleInRad) + buffY*cos(angleInRad);
    }
    
    // minute arrow
    glBegin(GL_POLYGON);
    glColor3f(0.5, 0.5, 0.5);
    glVertex3f(b.x[0], b.y[0], -0.511);
    glVertex3f(b.x[1], b.y[1], -0.511);
    glVertex3f(b.x[2], b.y[2], -0.511);
    glEnd();
    b = f;
    
    angleInRad = Calc_Sec(seconds) * 3.14159265 / 180.;
    f = c;
    for (int i = 0; i < 3; i++)
    {
        double buffX = c.x[i], buffY = c.y[i];
        c.x[i] = buffX*cos(angleInRad) + buffY*sin(angleInRad);
        c.y[i] = -buffX*sin(angleInRad) + buffY*cos(angleInRad);
    }
    
    // second arrow
    glBegin(GL_POLYGON);
    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(c.x[0], c.y[0], -0.51);
    glVertex3f(c.x[1], c.y[1], -0.51);
    glVertex3f(c.x[2], c.y[2], -0.51);
    glEnd();
    c = f;
}

void Clock::drawNumbers()
{
    
    /* 12 */
    glLineWidth(4);
    glBegin(GL_LINES);
    glColor3d(0, 0, 0);
    glVertex3f(-0.05, 0.4, -0.5001);
    glVertex3f(-0.01, 0.35, -0.5001);
    glVertex3f(-0.01, 0.4, -0.5001);
    glVertex3f(-0.05, 0.35, -0.5001);
    glVertex3f(0.02, 0.4, -0.5001);
    glVertex3f(0.02, 0.35, -0.5001);
    glVertex3f(0.05, 0.4, -0.5001);
    glVertex3f(0.05, 0.35, -0.5001);
    glEnd();
    
    /*3*/
    
    glLineWidth(4);
    glBegin(GL_LINES);
    glColor3d(0, 0, 0);
    glVertex3f(0.41, 0.025, -0.5001);
    glVertex3f(0.41, -0.025, -0.5001);
    glVertex3f(0.38, 0.025, -0.5001);
    glVertex3f(0.38, -0.025, -0.5001);
    glVertex3f(0.35, -0.025, -0.5001);
    glVertex3f(0.35, 0.025, -0.5001);
    glEnd();
    
    /*6*/
    
    glLineWidth(4);
    glBegin(GL_LINES);
    glColor3d(0, 0, 0);
    glVertex3f(-0.04, -0.35, -0.5001);
    glVertex3f(-0.02, -0.4, -0.5001);
    glVertex3f(-0.02, -0.4, -0.5001);
    glVertex3f(0.00, -0.35, -0.5001);
    glVertex3f(0.03, -0.35, -0.5001);
    glVertex3f(0.03, -0.4, -0.5001);
    glEnd();
    
    /*9*/
    
    glLineWidth(4);
    glBegin(GL_LINES);
    glColor3d(0, 0, 0);
    glVertex3f(-0.39, 0.025, -0.5001);
    glVertex3f(-0.35, -0.025, -0.5001);
    glVertex3f(-0.35, 0.025, -0.5001);
    glVertex3f(-0.39, -0.025, -0.5001);
    glVertex3f(-0.41, 0.025, -0.5001);
    glVertex3f(-0.41, -0.025, -0.5001);
    glEnd();
}

void Clock::drawLines()
{
    double xCoord1 = 0.0, yCoord1 = 0.46, xCoord2 = 0.0, yCoord2 = 0.48;
    
    glLineWidth(2);
    glBegin(GL_LINES);
    glColor3d(0, 0, 0);
    double angle = 0.0;
    while (angle < 360)
    {
        double angleInRad = angle * 3.14159265 / 180., x1, x2, y1, y2;
        x1 = xCoord1*cos(angleInRad) + yCoord1*sin(angleInRad);
        y1 = -xCoord1*sin(angleInRad) + yCoord1*cos(angleInRad);
        x2 = xCoord2*cos(angleInRad) + yCoord2*sin(angleInRad);
        y2 = -xCoord2*sin(angleInRad) + yCoord2*cos(angleInRad);
        glVertex3f(x1, y1, -0.5001);
        glVertex3f(x2, y2, -0.5001);
        angle += 30;
    }
    glEnd();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_SMOOTH | GL_LIGHT1);
    glLoadIdentity();
    glRotatef(task.rotate_x, 1.0, 0.0, 0.0);
    glRotatef(task.rotate_y, 0.0, 1.0, 0.0);
    task.drawArrays();
    task.drawCircle();
    task.drawLines();
    task.drawNumbers();
    task.drawArrays();
    task.drawCube();
    glFlush();
    glutSwapBuffers();
    glutPostRedisplay();
}

void specialKeys(int key, int x, int y) {
    
    //  Right arrow - increase rotation by 5 degree
    if (key == GLUT_KEY_RIGHT)
        task.rotate_y += 5;
    
    //  Left arrow - decrease rotation by 5 degree
    else if (key == GLUT_KEY_LEFT)
        task.rotate_y -= 5;
    
    else if (key == GLUT_KEY_UP)
        task.rotate_x += 5;
    
    else if (key == GLUT_KEY_DOWN)
        task.rotate_x -= 5;
    glDisable(GL_LIGHT1);
    //  Request display update
    glutPostRedisplay();
    
}
