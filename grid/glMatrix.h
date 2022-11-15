#ifndef HEADER_GLUT_MATRIX
#define HEADER_GLUT_MATRIX

#include <vector>
#include <iostream>
#include <cmath>
// #include "glOrigin.h"

using namespace std;

vector<vector<float>> matrixMultiplication(const vector<vector<float>> &A, const vector<vector<float>> &B)
{
    vector<vector<float>> res;
    if (A.size() == 0 || B.size() == 0)
        return res;
    if (A[0].size() != B.size())
    {
        cout << "Mat_mul invalid";
        exit(-1);
        return res;
    }
    res = vector<vector<float>>(A.size(), vector<float>(B[0].size(), 0));
    for (int i = 0; i < A.size(); i++)
    {
        for (int j = 0; j < B[0].size(); j++)
        {
            for (int k = 0; k < A[0].size(); k++)
            {
                res[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return res;
}

vector<vector<float>> identityMatrix()
{
    vector<vector<float>> I(4, vector<float>(4, 0));
    I[0][0] = 1;
    I[1][1] = 1;
    I[2][2] = 1;
    I[3][3] = 1;
    return I;
}

vector<vector<float>> translateMatrix(float x, float y, float z)
{
    vector<vector<float>> T = identityMatrix();
    T[0][3] = x;
    T[1][3] = y;
    T[2][3] = z;
    return T;
}

vector<vector<float>> XrotateMatrix(float theta)
{
    vector<vector<float>> R(4, vector<float>(4, 0));
    R[0][0] = 1;
    R[1][1] = cos(theta);
    R[1][2] = -sin(theta);
    R[2][1] = -R[1][2];
    R[2][2] = R[1][1];
    R[3][3] = 1;
    return R;
}

vector<vector<float>> YrotateMatrix(float theta)
{
    vector<vector<float>> R(4, vector<float>(4, 0));
    R[0][0] = cos(theta);
    R[0][2] = sin(theta);
    R[2][0] = -R[0][2];
    R[2][2] = R[0][0];
    R[1][1] = 1;
    R[3][3] = 1;
    return R;
}

vector<vector<float>> ZrotateMatrix(float theta)
{
    vector<vector<float>> R(4, vector<float>(4, 0));
    R[0][0] = cos(theta);
    R[0][1] = -sin(theta);
    R[1][0] = -R[0][1];
    R[1][1] = R[0][0];
    R[2][2] = 1;
    R[3][3] = 1;
    return R;
}

// vector<vector<float>> rotateMatrix(vector<vector<float>> R, bool isBase = false)
// {
//     if (!isBase)
//         return R;
//     vector<vector<float>> T = translateMatrix(-glOrigin.x, -glOrigin.y, -glOrigin.z);
//     T = matrixMultiplication(R, T);
//     T = matrixMultiplication(translateMatrix(glOrigin.x, glOrigin.y, glOrigin.z), T);
//     return T;
// }

void printMatrix(vector<vector<float>> p)
{
    for (auto it : p)
    {
        for (auto iter : it)
            printf("%.2f \t", iter);
        cout << endl;
    }
    cout << "-----------------\n";
}

#endif