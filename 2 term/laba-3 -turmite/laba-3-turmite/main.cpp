//
//  main.cpp
//  laba-3(turmite)
//
//  Created by Андрей Пригода on 25.04.17.
//  Copyright © 2017 Андрей Пригода. All rights reserved.
//

#include "Turmite.h"
#include <GLUT/GLUT.h>
#include <OpenGL/OpenGL.h>

//void Display ()
//{
//    Turmite f;
//    f.draw();
//}


int main(int argc, char **argv)
{
   
    Turmite mite = Turmite::read("rules.txt");
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
    glutInitWindowSize(300, 300);
    glutCreateWindow("Turmite");
    glutDisplayFunc(mite.draw());
    mite.simulate();
}
