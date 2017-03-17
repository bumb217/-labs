#ifndef GRID_H
#define GRID_H

#include "sceneobject.h"

class Grid : public SceneObject
{
protected:
   GLfloat countCells;
   GLfloat cellSize;
   QVector<GLbyte> colors;
   virtual void addColor(GLbyte r, GLbyte g, GLbyte b);
public:
    Grid(uint size = 10, GLfloat cellSize = 1);
    void setSize(uint size, GLfloat cellSize);
    uint getCellsCount() const {return countCells;}
    GLfloat getCellSize() const {return cellSize;}
    virtual void draw();
};

#endif // GRID_H
