#ifndef HEADER_GLUT_PATH
#define HEADER_GLUT_PATH

#include <vector>
#include "glMatrix.h"
#include "glProjection.h"
#include "glOrigin.h"
#include <GL/glut.h>

using namespace std;

class glutPath
{
public:
    vector<vector<float>> original, after;
    vector<vector<float>> process;
    float center[4] = {0, 0, 0, 1};
    float color[3];

    glutPath(float r = 0, float g = 0, float b = 0)
    {
        original.resize(4);
        after.resize(4);
        process = identityMatrix();
        setColor(r, g, b);
    }
    glutPath(float x1, float y1, float z1, float x2, float y2, float z2, float r = 0, float g = 0, float b = 0)
    {
        original.resize(4);
        after.resize(4);
        process = identityMatrix();
        insert(x1, y1, z1);
        insert(x2, y2, z2);
        setColor(r, g, b);
    }

    void setColor(float r, float g, float b)
    {
        color[0] = r;
        color[1] = g;
        color[2] = b;
    }

    void insert(float x, float y, float z)
    {
        original[0].push_back(x);
        original[1].push_back(y);
        original[2].push_back(z);
        original[3].push_back(1);
        center[0] += x;
        center[1] += y;
        center[2] += z;
        center[0] /= original[0].size();
        center[1] /= original[0].size();
        center[2] /= original[0].size();
    }

    void updateProcess()
    {
        after = matrixMultiplication(process, original);
    }

    void translate(float x, float y, float z)
    {
        process = matrixMultiplication(translateMatrix(x, y, z), process);
    }

    void rotateX(float theta, bool isBase = false)
    {
        process = matrixMultiplication(XrotateMatrix(theta), process);
    }

    void rotateY(float theta, bool isBase = false)
    {
        process = matrixMultiplication(YrotateMatrix(theta), process);
    }

    void rotateZ(float theta, bool isBase = false)
    {
        process = matrixMultiplication(ZrotateMatrix(theta), process);
    }

    void show(bool isBase = false)
    {
        updateProcess();
        after = matrixMultiplication(glOrigin.process, after);
        glProjection.project(after);
        glColor3f(color[0], color[1], color[2]);
        glBegin(GL_LINES);
        for (int i = 0; i < after[0].size() - 1; i++)
        {
            glVertex3s(after[0][i], after[1][i], after[2][i]);
            glVertex3s(after[0][i + 1], after[1][i + 1], after[2][i + 1]);
        }
        glEnd();
    }

    void reset()
    {
        process = identityMatrix();
    }

    void clear()
    {
        original.clear();
        original.resize(4);
        process = identityMatrix();
    }
};

#endif