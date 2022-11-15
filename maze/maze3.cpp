#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <unistd.h>
#include <GL/glut.h>
#include "history.h"
#include "glOrigin.h"
#include "glCuboid.h"

using namespace std;

time_t startTime, endTime;
vector<vector<float>> levelData;
int mazeLevel = 1;
glutPath pathFollowed(1, 0.3, 0.3);
float pathLength = 0;
float timeTaken = 0;
vector<vector<bool>> freeSpace;
glutCuboid redBox(10, 10, 10, 20, 20, 20);

class GlPrint{
public:
    bool isStart = true;
    bool gameOver = false;
    void glPrint(GLfloat x, GLfloat y, string showStr){
        glTranslatef(x, y, 0);
        for (int i = 0; i < showStr.size(); i++){
            glutStrokeCharacter(GLUT_STROKE_ROMAN, showStr[i]);
        }
    }

    void theEnd(GLfloat x, GLfloat y){
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_BLEND);
        glEnable(GL_LINE_SMOOTH);
        glPushMatrix();
        glScalef(0.4, 0.4, 1);
        glPrint(x, y, "You Win");
        glPrint(x-720, y-330, "Path length covered: "+to_string((int)pathLength));
        glPrint(x-1400, y-330, "Time Taken: "+to_string(timeTaken)+" sec");
        // glPrint(x-1400, y-330, );
        // glPrint(x-600, y-380, to_string((int)pathLength));
        // glPrint(x-1500, y-340, "Press any key to continue...");
        glPopMatrix();
    }

    void start(GLfloat x, GLfloat y){
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_BLEND);
        glEnable(GL_LINE_SMOOTH);
        glPushMatrix();
        glScalef(0.4, 0.4, 1);
        glPrint(x, y, "Level-"+to_string(mazeLevel));
        glPopMatrix();
    }
};

GlPrint printScreen;

void ifGameOver(){
    // 385 205 15
    if(redBox.center[0]==385 && redBox.center[1]==205 && redBox.center[2]==15){
        time(&endTime);
        timeTaken = endTime - startTime;
        updateLevel(mazeLevel, timeTaken, pathLength);
        timeTaken = int(timeTaken*100)/100.0;
        cout << "Time taken : " << timeTaken << " sec " << "\n";
        printScreen.gameOver = true;
        cout << "you win with path length " << pathLength << "\n";
    }
}

void ifPossible(float x, float y, float z){
    if(redBox.center[0]+x+5 >= freeSpace[0].size() || redBox.center[1]+y+5 >= freeSpace.size() || redBox.center[0]+x < 5 || redBox.center[1]+y < 5 || redBox.center[2]+z > 20 || redBox.center[2]+z < -20)
        return;
    if(!freeSpace[redBox.center[1]+y+5][redBox.center[0]+x+5] || !freeSpace[redBox.center[1]+y-5][redBox.center[0]+x-5])
        return;
    pathFollowed.insert(redBox.center[0]+x, redBox.center[1]+y, redBox.center[2]+z);
    pathLength += sqrt(x*x + y*y + z*z)/10;
    redBox.translate(x, y, z);
    ifGameOver();
    return;
}

class walls{
public:
    vector<glutCuboid> wallUnits;
    
    vector<vector<float>> xWalls = {
        {0, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {0, 1, 0, 0, 1, 0, 0, 1, 1, 0},
        {0, 1, 1, 1, 0, 1, 0, 0, 0, 1},
        {1, 0, 0, 1, 0, 0, 1, 1, 0, 0},
        {0, 1, 1, 0, 0, 1, 1, 0, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
    };

    vector<vector<float>> yWalls = {
        {1, 1, 1, 1, 1},
        {0, 1, 0, 0, 0},
        {0, 0, 1, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 1, 0, 1},
        {0, 1, 0, 1, 0},
        {1, 0, 1, 0, 1},
        {0, 1, 0, 1, 0},
        {0, 1, 1, 0, 0},
        {0, 0, 1, 0, 0},
        {1, 1, 1, 1, 1}
    };

    int row = yWalls[0].size(), col = xWalls[0].size();
    float height = 20;

    walls(){

        // cout << col << ", " << row << "\n";
        freeSpace.resize(40*row+11, vector<bool>(40*col+11, true));
        for(int i = 0; i < row+1; i++){
            for(int j = 0; j < col+1; j++){
                glutCuboid temp(j*40, i*40, 0, j*40+10, i*40+10, height);
                wallUnits.push_back(temp);
                for(int x = j*40; x <= j*40+10; x++) for(int y = i*40; y <= i*40+10; y++) freeSpace[y][x] = false;
            }
        }
        for(int i = 0; i < row+1; i++){
            for(int j = 0; j < col; j++){
                if(xWalls[i][j]){
                    glutCuboid temp(j*40+10, i*40, 0, j*40+40, i*40+10, height);
                    wallUnits.push_back(temp);
                    for(int x = j*40+10; x <= j*40+40; x++) for(int y = i*40; y <= i*40+10; y++) freeSpace[y][x] = false;
                }
            }
        }
        for(int i = 0; i < col+1; i++){
            for(int j = 0; j < row; j++){
                if(yWalls[i][j]){
                    glutCuboid temp(i*40, j*40+10, 0, i*40+10, j*40+40, height);
                    wallUnits.push_back(temp);
                    for(int x = i*40; x <= i*40+10; x++) for(int y = j*40+10; y <= j*40+40; y++) freeSpace[y][x] = false;
                }
            }
        }
    }

    void show(){
        for(glutCuboid &w : wallUnits){
            w.show();
        }
    }
};

walls maze;

bool start = true;

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    glLineWidth(5.0);
    if(printScreen.isStart){
        printScreen.start(-280, 0);
        glFlush();
        printScreen.isStart = false;
        time(&startTime);
        ios_base::sync_with_stdio(false);
    }
    else if(printScreen.gameOver){
        printScreen.theEnd(-280, 130);
        glFlush();
        sleep(5);
        exit(0);
    }
    else{
        maze.show();
        pathFollowed.show();
        redBox.show();
        glFlush();
    }
}

bool flag = false;

void keyboard(unsigned char key, int x, int y)
{
    float sp = 10;              // pixel per click
    float rotationSpeed = 0.02; // angle per click
    
    if(printScreen.gameOver){
        // sleep(5);
        // exit(0);
        return;
    }
    else if (flag)
    {
        if (key == 'w')
            glOrigin.translate(0, sp, 0);
        else if (key == 's')
            glOrigin.translate(0, -sp, 0);
        else if (key == 'd')
            glOrigin.translate(sp, 0, 0);
        else if (key == 'a')
            glOrigin.translate(-sp, 0, 0);
        else if (key == 'o')
            glOrigin.translate(0, 0, sp);
        else if (key == 'i')
            glOrigin.translate(0, 0, -sp);
        else if (key == 'x')
            glOrigin.rotateX(rotationSpeed);
        else if (key == 'y')
            glOrigin.rotateY(rotationSpeed);
        else if (key == 'z')
            glOrigin.rotateZ(rotationSpeed);
        else if (key == 'X')
            glOrigin.rotateX(-rotationSpeed);
        else if (key == 'Y')
            glOrigin.rotateY(-rotationSpeed);
        else if (key == 'Z')
            glOrigin.rotateZ(-rotationSpeed);
        else if (key == 'r'){
            glOrigin.reset();
            glOrigin.translate(-120, -30, 320);
            glOrigin.rotateX(-.1);
            glOrigin.rotateY(0.3);
        }
    }
    else
    {
        if (key == 'w'){
            ifPossible(0, sp, 0);
        }
        else if (key == 's'){
            ifPossible(0, -sp, 0);
        }
        else if (key == 'd'){
            ifPossible(sp, 0, 0);
        }
        else if (key == 'a'){
            ifPossible(-sp, 0, 0);
        }
        else if (key == 'i')
            redBox.translate(0, 0, -sp);
        else if (key == 'o')
            redBox.translate(0, 0, sp);
        else if (key == 'x')
            redBox.rotateX(rotationSpeed);
        else if (key == 'y')
            redBox.rotateY(rotationSpeed);
        else if (key == 'z')
            redBox.rotateZ(rotationSpeed);
        else if (key == 'X')
            redBox.rotateX(-rotationSpeed);
        else if (key == 'Y')
            redBox.rotateY(-rotationSpeed);
        else if (key == 'Z')
            redBox.rotateZ(-rotationSpeed);
        else if (key == 'r'){
            redBox.reset();
            pathFollowed.clear();
            pathFollowed.insert(redBox.center[0], redBox.center[1], redBox.center[1]);
        }
        else if (key == 'q')
            redBox.rotate(rotationSpeed, 1, 7, 13);
    }
    glutPostRedisplay();
}

void mouse(int button, int state, int x, int y)
{
    switch (button)
    {
    case GLUT_LEFT_BUTTON:
        if (state == GLUT_DOWN)
            flag = true;
        else
            flag = false;
        break;
    default:
        break;
    }
}

void vgl_init(int &argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1362, 750);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("3D Transformations");
    glClearColor(0.6, 0.8, 0.9, 5.0);
    glOrtho(-454.0, 454.0, -250.0, 250.0, -250.0, 250.0);
    glEnable(GL_DEPTH_TEST);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glShadeModel(GL_SMOOTH); // Enable Smooth Shading
    glClearDepth(1.0f);      // Depth Buffer Setup
                             // glEnable(GL_DEPTH_TEST); // Enables Depth Testing
    glutMainLoop();
}

int main(int argc, char **argv)
{
    glOrigin.translate(-120, -30, 320);
    glOrigin.rotateX(-.1);
    glOrigin.rotateY(0.3);

    levelData = readLevel();
    cout << "Level - " << mazeLevel << "\n";
    pathFollowed.insert(redBox.center[0], redBox.center[1], redBox.center[1]);
    redBox.setColor(1, 0, 0);

    vgl_init(argc, argv);

    return 0;
}

// 385 205 15