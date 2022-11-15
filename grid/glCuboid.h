#ifndef HEADER_GLUT_CUBOID
#define HEADER_GLUT_CUBOID

#include <vector>
#include "glPlane.h"

using namespace std;

class glutCuboid
{
public:
    float p1[3], p2[3];
    vector<glutPlane> planes;
    float center[3];

    glutCuboid(float x1, float y1, float z1, float x2, float y2, float z2)
    {
        p1[0] = x1;
        p1[1] = y1;
        p1[2] = z1;
        p2[0] = x2;
        p2[1] = y2;
        p2[2] = z2;

        center[0] = (p1[0] + p2[0]) / 2;
        center[1] = (p1[1] + p2[1]) / 2;
        center[2] = (p1[2] + p2[2]) / 2;

        glutPlane p;
        p.setColor(75 / 256.0, 0 / 256.0, 130 / 256.0);
        p.insert(p1[0], p1[1], p1[2]);
        p.insert(p1[0], p1[1], p2[2]);
        p.insert(p1[0], p2[1], p2[2]);
        p.insert(p1[0], p2[1], p1[2]);
        planes.push_back(p);

        p.clear();
        p.insert(p2[0], p1[1], p1[2]);
        p.insert(p2[0], p1[1], p2[2]);
        p.insert(p2[0], p2[1], p2[2]);
        p.insert(p2[0], p2[1], p1[2]);
        planes.push_back(p);

        p.clear();
        p.insert(p1[0], p1[1], p1[2]);
        p.insert(p1[0], p1[1], p2[2]);
        p.insert(p2[0], p1[1], p2[2]);
        p.insert(p2[0], p1[1], p1[2]);
        planes.push_back(p);

        p.clear();
        p.insert(p1[0], p2[1], p1[2]);
        p.insert(p1[0], p2[1], p2[2]);
        p.insert(p2[0], p2[1], p2[2]);
        p.insert(p2[0], p2[1], p1[2]);
        planes.push_back(p);

        p.clear();
        p.insert(p1[0], p1[1], p1[2]);
        p.insert(p1[0], p2[1], p1[2]);
        p.insert(p2[0], p2[1], p1[2]);
        p.insert(p2[0], p1[1], p1[2]);
        planes.push_back(p);

        p.clear();
        p.insert(p1[0], p1[1], p2[2]);
        p.insert(p1[0], p2[1], p2[2]);
        p.insert(p2[0], p2[1], p2[2]);
        p.insert(p2[0], p1[1], p2[2]);
        planes.push_back(p);
    }

    void setColor(float r, float g, float b)
    {
        for (glutPlane &p : planes)
        {
            p.setColor(r, g, b);
        }
    }

    void translate(float x, float y, float z)
    {
        for (glutPlane &p : planes)
        {
            p.translate(x, y, z);
        }
        center[0] += x;
        center[1] += y;
        center[2] += z;
    }

    void rotateX(float theta)
    {
        for (glutPlane &p : planes)
        {
            p.translate(0, -center[1], -center[2]);
            p.rotateX(theta);
            p.translate(0, center[1], center[2]);
        }
    }

    void rotateY(float theta)
    {
        for (glutPlane &p : planes)
        {
            p.translate(-center[0], 0, -center[2]);
            p.rotateY(theta);
            p.translate(center[0], 0, center[2]);
        }
    }

    void rotateZ(float theta)
    {
        for (glutPlane &p : planes)
        {
            p.translate(-center[0], -center[1], 0);
            p.rotateZ(theta);
            p.translate(center[0], center[1], 0);
        }
    }

    void rotate(float theta, float a, float b, float c)
    {
        float alpha, beta, d, D;
        d = sqrt(a * a + c * c);
        D = sqrt(a * a + b * b + c * c);
        alpha = asin(c / d);
        beta = asin(b / D);
        for (glutPath &p : planes)
        {
            p.translate(-center[0], -center[1], -center[2]);
            p.rotateY(alpha);
            p.rotateZ(-beta);
            p.rotateX(theta);
            p.rotateZ(beta);
            p.rotateY(-alpha);
            p.translate(center[0], center[1], center[2]);
        }
    }

    void show()
    {
        for (glutPlane &p : planes)
        {
            p.show(true);
        }
    }

    void reset()
    {
        for (glutPlane &p : planes)
        {
            p.reset();
        }
        center[0] = (p1[0] + p2[0]) / 2;
        center[1] = (p1[1] + p2[1]) / 2;
        center[2] = (p1[2] + p2[2]) / 2;
    }
};

#endif