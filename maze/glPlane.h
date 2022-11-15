#ifndef HEADER_GLUT_PLANE
#define HEADER_GLUT_PLANE

#include "glPath.h"
// #include "glBase.h"

class glutPlane : public glutPath
{
public:
    glutPlane(float r = 0, float g = 0, float b = 1)
    {
        setColor(r, g, b);
    }

    void show(bool outLine)
    {
        updateProcess();
        after = matrixMultiplication(glOrigin.process, after);
        glProjection.project(after);
        glColor3f(color[0], color[1], color[2]);
        glBegin(GL_POLYGON);
        for (int i = 0; i < after[0].size(); i++)
        {
            glVertex3s(after[0][i], after[1][i], after[2][i]);
        }
        glEnd();
    }
};

#endif