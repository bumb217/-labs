#include "pyramid.h"

Pyramid::Pyramid(float size):Figure()
{
    this->size = size;

    type = 1;
    pos = QVector3D(0,0,0);


    double r = sqrt(6)/4;
    double h = sqrt(2)*r;
    double d = 1/(2*sqrt(6));
    QVector3D s(0, h-d, 0);
    QVector3D a0(r, -d, 0);
    QVector3D a1(r*cos(2*M_PI/3), -d, -r*sin(2*M_PI/3));
    QVector3D a2(r*cos(4*M_PI/3), -d, -r*sin(4*M_PI/3));


    addPoint(a0);
    addPoint(a1);
    addPoint(a2);

    addPoint(a0);
    addPoint(s);
    addPoint(a1);

    addPoint(a1);
    addPoint(s);
    addPoint(a2);

    addPoint(a2);
    addPoint(s);
    addPoint(a0);

    qDebug() << a0.distanceToPoint(a1) << a1.distanceToPoint(a2)
                << a2.distanceToPoint(a0) << a0.distanceToPoint(s);



    indices ={
        0,1,2,
        3,4,5,
        6,7,8,
        9,10,11
    };


    setPlaneColor(0, QColor(255,0,0));
    setPlaneColor(1, QColor(0,255,0));
    setPlaneColor(2, QColor(0,0,255));
    setPlaneColor(3, QColor(255,0,255));

    //rainbow();

    recalcTransform();
}

void Pyramid::recalcTransform()
{
    Figure::recalcTransform();
    transform.scale(size);
}

void Pyramid::setPlaneColor(uint num, const QColor &color)
{
    Figure::setPlaneColor(num, color);
    for (int i = 0; i < 9; i+=3)
    {
        vertexColors[num*9+i] = color.red();
        vertexColors[num*9+i+1] = color.green();
        vertexColors[num*9+i+2] = color.blue();
    }
}

void Pyramid::draw()
{
    glPushMatrix();
    glMultMatrixf(transform.constData());

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    glVertexPointer(3, GL_FLOAT , 0, points.data());
    glColorPointer(3, GL_UNSIGNED_BYTE, 0, vertexColors);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_BYTE, indices.data());

    glDisableClientState(GL_COLOR_ARRAY);
    if (selected)
    {
        glColor3f(1,1,1);
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_BYTE, indices.data());
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }

    glDisableClientState(GL_VERTEX_ARRAY);

    glPopMatrix();
}

void Pyramid::drawGeometryOnly()
{
    glPushMatrix();
    glMultMatrixf(transform.constData());

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT , 0, points.data());
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_BYTE, indices.data());
    glDisableClientState(GL_VERTEX_ARRAY);

    glPopMatrix();
}

void Pyramid::rainbow()
{
    for (int i = 0; i < 36; i+=3)
    {
        int r = rand()%3;
        vertexColors[i] = 250*(r==0);
        vertexColors[i+1] = 250*(r==1);
        vertexColors[i+2] = 250*(r==2);
    }
}
