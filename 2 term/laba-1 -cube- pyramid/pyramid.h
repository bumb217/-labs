#ifndef PYRAMID_H
#define PYRAMID_H

#include "figure.h"

class Pyramid : public Figure
{
protected:
     QColor planeColors[4];
     GLubyte vertexColors[36];
     GLfloat size;
     void recalcTransform();
public:
    Pyramid(float size = 1);
    virtual void draw();
    virtual void drawGeometryOnly();
    virtual void setPlaneColor(uint num, const QColor &color);
    virtual uint countPlanes() const {return 4;}
    virtual void scale(float s){size += s; recalcTransform();}
    virtual void rainbow();
    virtual double getSize(){return size;}
};

#endif // PYRAMID_H
