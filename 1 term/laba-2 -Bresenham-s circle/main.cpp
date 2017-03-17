#include <math.h>
#include <stdio.h>
#include <algorithm>
#include <vector>
#include <list>
#include <time.h>
#include <stdlib.h>
#define Int GLint
#define Float GLfloat
#define inf 0x3f3f3f3f
using namespace std;
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <OpenGL/gl3.h>
#include <OpenGL/OpenGL.h>
#define __gl_h_

int width = 800, height = 800; // ширина и высота окна

class Circle
{
public:
    Circle(int _x0 = width + 1, int _y0 = height + 1, int _r = 0) { x0 = _x0; y0 = _y0; r = _r; } // конструктор класса
    void drawCircle(); // функция-член рисования окружности
    void drawPixel(int &, int &); // закрасить пиксель и симметричные ему ( 8 точек на кривой )
    int x0, y0, r; // (x0, y0) - координаты центра окружности, r - радиус
};

Circle _circle; // создание объекта _circle типа Circle

int dis(int x, int y)
{
    return x * x + y * y; // Вычисление расстояния от (0, 0) до (x, y), возведенное в квадрат
}

void Circle::drawPixel(int & x, int & y)
{
    glColor3f(1, 1, 1);
    glBegin(GL_POINTS);
    glVertex2i(x0 + x, y0 + y);
    glVertex2i(x0 - x, y0 + y);
    glVertex2i(x0 + x, y0 - y);
    glVertex2i(x0 - x, y0 - y);
    glVertex2i(x0 + y, y0 + x);
    glVertex2i(x0 - y, y0 + x);
    glVertex2i(x0 + y, y0 - x);
    glVertex2i(x0 - y, y0 - x);
    glEnd();
}

void Circle::drawCircle()
{
    int x = 0, y = r; // начинаем рисовать окружность с точки (0, r). Смещение окружности через координаты центра учитывается в функции Circle::drawPixel(Int &, Int &). В дальнейшем (x, y) - это текущая точка рисования
    while(y >= (r >> 1)) // текущая координата y изменяется от r до r / 2 (строим 1/8 окружности)
    {
        drawPixel(x, y); // по текущей точке рисования получаем 8 точек на кривой окружности и закрашиваем их
        int move[3]; // массив расстояний до 3 точек, в которые можно перейти из текущей для последующего их закрашивания
        move[0] = fabs(dis(x + 1, y) - r * r); // вычисляем расстояние от (x + 1, y) до кривой окружности
        move[1] = fabs(dis(x, y - 1) - r * r); // вычисляем расстояние от (x, y - 1) до кривой окружности
        move[2] = fabs(dis(x + 1, y - 1) - r * r); // вычисляем расстояние от (x + 1, y - 1) до кривой окружности
        switch(min_element(move, move + 3) - move) // switch ( X ), X принадлежит {0, 1, 2}, где move[X] - это min(move[0], move[1], move[2]). То есть определяем позицию в массиве move с минимальным значением
        {
            case 0: x++; break; // Если эта позиция = 0, т.е move[0] > move[1] и move[0] > move[2], то перемещаемся в точку (x + 1, y)
            case 1: y--; break; // Если эта позиция = 1, т.е move[1] > move[0] и move[1] > move[2], то перемещаемся в точку (x, y - 1)
            case 2: x++; y--; break; // Если эта позиция = 2, т.е move[2] > move[0] и move[2] > move[1], то перемещаемся в точку (x + 1, y - 1)
        }
        // Полученная точка (x, y) - текущая
    }
}

void display() // функция вывода на экран изображения
{
    glClear(GL_COLOR_BUFFER_BIT);
    _circle.drawCircle(); // вызываем метод drawCircle объекта _circle
    glutSwapBuffers();
}

void reshape(int w, int h) // функция смещения и изменения размеров окна
{
    glClearColor(0, 0, 0, 0);
    glViewport(0, 0, fmin(w, h), fmin(w, h));
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, width, 0, height, -1, 1); // используем ортографическую проекцию
}

void timer(int)
{
    display();
    glutTimerFunc(60, timer, 0);
}

void mouse(int button, int state, int x, int y)
{
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
        _circle = Circle(width / 2, height / 2, 100); // при нажатии левой кнопки мыши - рисуем окружность центре окна, в точке (width / 2, height / 2) с радиусом 100
    if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
        _circle.x0 = width + 1, _circle.y0 = height + 1, _circle.r = 0; // при нажатии правой кнопки мыши удаляем окружность
}

void key(int key, int x, int y)
{
    if(key == GLUT_KEY_UP && _circle.r + 5 < width / 2)
        _circle.r += 5; // при нажатии клавиши UP на клавиатуре увеличивается радиус на 5
    if(key == GLUT_KEY_DOWN && _circle.r - 5 > 0)
        _circle.r -= 5; // при нажатии клавиши DOWN на клавиатуре уменьшается радиус на 5
}


int main(int argc, const char * argv[])
{
//    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowPosition(200, 200);
    glutInitWindowSize(800, 800);
    glutCreateWindow("окружность");
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutSpecialFunc(key);
    glutTimerFunc(60, timer, 0);
    glutMainLoop(); 
    return 0;
}
