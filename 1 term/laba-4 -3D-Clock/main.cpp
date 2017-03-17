//
//  main.cpp
//  laba-4
//
//  Created by Андрей Пригода on 24.01.17.
//  Copyright © 2017 Андрей Пригода. All rights reserved.
//

#include "clock.hpp"


int main(int argc, char* argv[])
{
    Clock cl;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(700, 700);
    glutCreateWindow("3D-Clock");
    glEnable(GL_DEPTH_TEST);
    glutDisplayFunc(display);
    glutSpecialFunc(specialKeys);
    glutMainLoop();
    return 0;
}
