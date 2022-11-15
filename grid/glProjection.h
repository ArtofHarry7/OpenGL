#ifndef HEADER_GLUT_POJECTION
#define HEADER_GLUT_POJECTION

#include <cmath>
#include <vector>

using namespace std;

class glutProjection
{
public:
    float x = 0, y = 0, z = 10;
    float l = 0, m = 0.05, n = 1;
    float eyeDistance = 300;
    float a, b, c, d;
    glutProjection()
    {
        deriveValues();
    }
    glutProjection(float l_, float m_, float n_, float x_, float y_, float z_, float d_)
    {
        update(l_, m_, n_, x_, y_, z_, d_);
    }

    void deriveValues()
    {
        float k = eyeDistance / sqrt(l * l + m * m + n * n);
        a = x + k * l;
        b = y + k * m;
        c = z + k * n;
        d = l * x + m * y + n * z;
    }

    void update(float l_, float m_, float n_, float x_, float y_, float z_, float d_)
    {
        l = l_;
        m = m_;
        n = n_;
        x = x_;
        y = y_;
        z = z_;
        eyeDistance = d_;
        deriveValues();
    }

    void project(float &x_, float &y_, float &z_)
    {
        float k = (l * a + m * b + n * c - d) / (l * (a - x_) + m * (b - y_) + n * (c - z_));
        x_ = a + k * (x_ - a);
        y_ = b + k * (y_ - b);
        z_ = c + k * (z_ - c);
    }

    void project(vector<vector<float>> &points)
    {
        for (int i = 0; i < points[0].size(); i++)
        {
            project(points[0][i], points[1][i], points[2][i]);
        }
    }
};
glutProjection glProjection(0.3, 0.3, 1, 0, 0, 0, 600);

#endif