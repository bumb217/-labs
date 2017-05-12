//
//  painter.h
//  laba-3(turmite)
//
//  Created by Андрей Пригода on 25.04.17.
//  Copyright © 2017 Андрей Пригода. All rights reserved.
//

#ifndef painter_h
#define painter_h
#include <GLUT/GLUT.h>
#include <OpenGL/OpenGL.h>

//#include <Windows.h>

//#define COLOR0 RGB(255, 255, 255)
//
//#define COLOR1 RGB(255, 0, 0)
//#define COLOR2 RGB(0, 255, 0)
//#define COLOR3 RGB(0, 0, 255)
//
//#define COLOR4 RGB(255, 255, 0)
//#define COLOR5 RGB(255, 0, 255)
//#define COLOR6 RGB(0, 255, 255)

//void drawMite(HDC &hdc, int x, int y, int size, int col_index) {
void drawMite(int x, int y, int size, int col_index) {
    glBegin(GL_POINTS);
    

    int l_x = x - (size / 2);
    int r_x = x + (size / 2);
    
    int t_y = y - (size / 2);
    int b_y = y + (size / 2);
    
    
    switch (col_index) {

        case 0: glColor3ub(255, 255, 255); break;
        case 1: glColor3ub(255, 0, 0); break;
        case 2: glColor3ub(0, 255, 0); break;
        case 3: glColor3ub(0, 0, 255); break;
        case 4: glColor3ub(255, 255, 0); break;
        case 5: glColor3ub(255, 0, 255); break;
        case 6: glColor3ub(0, 255, 255); break;
    }
    
    for (int i = l_x; i <= r_x; i++)
    {
        for (int j = t_y; j <= b_y; j++)
        {
            glVertex2i(i, j);
            
        }
    }
    glutMainLoop();
    glEnd();

}

#endif /* painter_h */
