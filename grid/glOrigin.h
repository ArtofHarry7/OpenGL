#ifndef HEADER_GLUT_ORIGIN
#define HEADER_GLUT_ORIGIN

#include <vector>
#include "glMatrix.h"

using namespace std;

class glutOrigin
{
public:
    vector<vector<float>> process;
    int x = 0, y = 0, z = 0;
    glutOrigin()
    {
        process = identityMatrix();
    }
    void translate(float a, float b, float c)
    {
        process = matrixMultiplication(translateMatrix(a, b, c), process);
        x += a;
        y += b;
        z += c;
    }

    vector<vector<float>> rotateMatrix(vector<vector<float>> R)
    {
        vector<vector<float>> T = translateMatrix(-x, -y, -z);
        T = matrixMultiplication(R, T);
        T = matrixMultiplication(translateMatrix(x, y, z), T);
        return T;
    }

    void rotateX(float theta)
    {
        process = matrixMultiplication(rotateMatrix(XrotateMatrix(theta)), process);
    }

    void rotateY(float theta)
    {
        process = matrixMultiplication(rotateMatrix(YrotateMatrix(theta)), process);
    }

    void rotateZ(float theta)
    {
        process = matrixMultiplication(rotateMatrix(ZrotateMatrix(theta)), process);
    }

    void reset()
    {
        process = identityMatrix();
        x = y = z = 0;
    }
};
glutOrigin glOrigin;

#endif