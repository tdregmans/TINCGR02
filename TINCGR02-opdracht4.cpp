/*
    TINCGR02-opdracht4.cpp

    version 2 (final version)

    CMI-TI 22 TINCGR02
    Student: Thijs Dregmans (1024272)
    Inleveropdracht 4
    Last edited: 13-12-2022

    The assignment provides the template that I used.
    I have chosen to program this assignment using C++, because
    I want to learn more about C++.

    Requirements
        -   The application must run without errors.
        -   The application results in a visual cube, rotated round the y-axis with 30�.
        -   The cube can be seen as a set of lines. The lines are specified below.
        -   The application follow the following points:
            a. Use a function that multiplies a vector with a matrix
            b. Convert the co�rdinates to homogeneous values.
            c. Use a projection on all co�rdinates
            d. Use a transition matrix to project the co�rdinates upon the 2D screen.
            e. Use a transition matrix to rotate the cube.
        -   The application uses the matrices in the right order.
        -   Bonus: Create a function that multiplies a matrix with another matrix.

    Tests
        I test the application by checking all requirements.
        The first two requirements are easy to check.
        The other requirements, I check in this way:
        1.

    Design
        I use the template provided in the assignment:
        'projection.cpp'

        If I used a resource for building a function, I will
        put the URL in the code.

        In my design, there are 2 additional classes besides the classes in 'projection.cpp':
        -   Point
            In this class, I create an easy way to store the Points
        -   Cube
            The Points need to be connected in a certain way. In Cube::drawCube() this is done.
            With Cube::matrixOperation(Matrix), one can easily apply Matrices to all the Points.

        The cube has a number of corners:
        -   v1 = (-1, -1, -1)
        -   v2 = (1, -1, -1)
        -   v3 = (1, 1, -1)
        -   v4 = (-1, 1, -1)
        -   v5 = (-1, -1, 1)
        -   v6 = (1, -1, 1)
        -   v7 = (1, 1, 1)
        -   v8 = (-1, 1, 1)

        I use the following steps:
        1.  Define the corners of the cube -> points.
        2.  Define a cube with the points.
        3.  Define a Matrix for the projections.
        4.  Calculate a resulting Matrix.
        5.  Apply this Matrix on all points.
        6.  Draw lines between points.
        7.  Display Cube.

*/

#include <list>
#include <cmath>
#include <iostream>
#include <vector>

#define GL_SILENCE_DEPRECATION
#include <GL/gl.h>
#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif

#define Vector vector<float>
#define Matrix vector<Vector>


using namespace std;

class Line {
    public:
        int x1, y1, x2, y2;
        Line(int, int, int, int);
};

Line::Line(int x1, int y1, int x2, int y2) {
    this->x1 = x1;
    this->y1 = y1;
    this->x2 = x2;
    this->y2 = y2;
}

class Lines {
    int sizeX, sizeY;
    list<Line> lines;
    public:
        Lines(int, int);
        void addLine(int, int, int, int);
        void draw();
        void display();
};

Lines *currentInstance;

void display() {
    currentInstance->display();
}

void end(unsigned char key, int x, int y) {
    exit(0);
}

Lines::Lines(int x, int y) {
    sizeX = x;
    sizeY = y;
}

void Lines::display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1, 1, 1);
    glBegin(GL_LINES);
    for (auto &line: lines) {
        glVertex2i(line.x1, line.y1);
        glVertex2i(line.x2, line.y2);
    }
    glEnd();
    glFlush();
}

void Lines::draw() {
    int argc = 0;
    glutInit(&argc, NULL);
    glutInitDisplayMode(GLUT_RGBA);
    glutInitWindowSize(sizeX, sizeY);
    glutCreateWindow("Lines");
    glOrtho(0, sizeX, sizeY, 0, -1, 1);
    currentInstance = this;
    glutDisplayFunc(::display); // Cannot use instance function here, so must use function in global namespace
    glutKeyboardFunc(end);
    glutMainLoop();
}

void Lines::addLine(int x1, int y1, int x2, int y2) {
        if (x1 < sizeX && y1 < sizeY && x1 >= 0 && y1 >= 0 && x2 < sizeX && y2 < sizeY && x2 >= 0 && y2 >= 0) {
        lines.emplace_back(x1, y1, x2, y2);
    }
}

// Class Point, used to store point
class Point {
    public:
        float x, y, z, h;
        Point(float, float, float);
};

// Point constructor
Point::Point(float x, float y, float z) {
    this->x = x;
    this->y = y;
    this->z = z;
    this->h = 1;
    // parameter h is added to create homogeneous coordinates
}

// Class Cube, used to store Points, apply Matrices and drawing the Lines
class Cube {
    public:
        vector<Point> points;
        Cube(vector<Point>);
        void matrixOperation(Matrix);
        void drawCube();
};

// Cube constructor
Cube::Cube(vector<Point> points) {
    this->points = points;
}

// method for applying a projection Matrix on all points
void Cube::matrixOperation(Matrix m) {
    for (int pointIndex = 0; pointIndex < this->points.size(); pointIndex++) {
        // for all points, get point, calculate new values and insert new values
        Point point = this->points[pointIndex];

        float tempX = m[0][0] * point.x + m[0][1] * point.y + m[0][2] * point.z + m[0][3] * point.h;
        float tempY = m[1][0] * point.x + m[1][1] * point.y + m[1][2] * point.z + m[1][3] * point.h;
        float tempZ = m[2][0] * point.x + m[2][1] * point.y + m[2][2] * point.z + m[2][3] * point.h;

        this->points[pointIndex] = Point(tempX, tempY, tempZ);
    }
}

// function used to multiply 2 Matrices
Matrix matrixMultiplication(Matrix m1, Matrix m2) {
    // matrix m1 and m2 must be 4x4 matrices
    Matrix newMatrix = {{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};
    for (int x = 0; x < 4; x++) {
        for (int y = 0; y < 4; y++) {
            // for each value in the new Matrix, calculate new value
            float som = 0;
            for (int step = 0; step < 4; step++) {
                som += m1[x][step] * m2[step][y];
            }
            newMatrix[x][y] = som;
        }
    }
    return newMatrix;
}

// method for drawing lines that form the Cube
void Cube::drawCube() {
    /*
        The lines go between the points:
        -   v1v2, v2v3, v3v4, v4v1, v1v5, v2v6, v3v7, v4v8, v5v6, v6v7, v7v8, v8v5
    */

    Lines lines(640, 480);
    // draw points

    // addLine : v1v2
    lines.addLine(this->points[0].x, this->points[0].y, this->points[1].x, this->points[1].y);
    // addLine : v2v3
    lines.addLine(this->points[1].x, this->points[1].y, this->points[2].x, this->points[2].y);
    // addLine : v3v4
    lines.addLine(this->points[2].x, this->points[2].y, this->points[3].x, this->points[3].y);
    // addLine : v4v1
    lines.addLine(this->points[3].x, this->points[3].y, this->points[0].x, this->points[0].y);

    // addLine : v1v5
    lines.addLine(this->points[0].x, this->points[0].y, this->points[4].x, this->points[4].y);
    // addLine : v2v6
    lines.addLine(this->points[1].x, this->points[1].y, this->points[5].x, this->points[5].y);
    // addLine : v3v7
    lines.addLine(this->points[2].x, this->points[2].y, this->points[6].x, this->points[6].y);
    // addLine : v4v8
    lines.addLine(this->points[3].x, this->points[3].y, this->points[7].x, this->points[7].y);

    // addLine : v5v6
    lines.addLine(this->points[4].x, this->points[4].y, this->points[5].x, this->points[5].y);
    // addLine : v6v7
    lines.addLine(this->points[5].x, this->points[5].y, this->points[6].x, this->points[6].y);
    // addLine : v7v8
    lines.addLine(this->points[6].x, this->points[6].y, this->points[7].x, this->points[7].y);
    // addLine : v8v5
    lines.addLine(this->points[7].x, this->points[7].y, this->points[4].x, this->points[4].y);

    // display result
    lines.draw();
}

int main() {
    // testcode

    // Define points in space
    Point v1 = Point(-1, -1, -1);
    Point v2 = Point(1, -1, -1);
    Point v3 = Point(1, 1, -1);
    Point v4 = Point(-1, 1, -1);
    Point v5 = Point(-1, -1, 1);
    Point v6 = Point(1, -1, 1);
    Point v7 = Point(1, 1, 1);
    Point v8 = Point(-1, 1, 1);
    vector<Point> cubePoints = {v1, v2, v3, v4, v5, v6, v7, v8};

    // Make a Cube with the points
    Cube cube = Cube(cubePoints);

    // Transformation Matrices
    // Projections
    Matrix ortho = {
        {1, 0, 0, 0},
        {0, 1, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 1}
    };
    Matrix para = {
        {1, 0, 0.5, 0},
        {0, 1, 0.5, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 1}
    };
    // para is not used now

    // Rotations
    float theta = 45 * (M_PI / 180); // Rotate 45 Degrees in the Y-axis
    Matrix rotateInY = {
        {cos(theta), 0, sin(theta), 0},
        {0, 1, 0, 0},
        {-1 * sin(theta), 0, cos(theta), 0},
        {0, 0, 0, 1}
    };
    float theta2 = 35 * (M_PI / 180); // Rotate 35 Degrees in the -axis
    Matrix rotateInX = {
        {1, 0, 0, 0},
        {0, cos(theta2), -1 * sin(theta2), 0},
        {0, sin(theta2), cos(theta2), 0},
        {0, 0, 0, 1}
    };

    // Source: https://en.wikipedia.org/wiki/Rotation_matrix

    // Translations
    Matrix translate = {
        {100, 0, 0, 200},
        {0, 100, 0, 300},
        {0, 0, 100, 0},
        {0, 0, 0, 1}
    };

    // Calculate the resulting Matrix of; Rotation in the Y-axis, Rotation in the X-axis, shifting and orthographic projection, to get the Isometric projection
    Matrix result = matrixMultiplication(rotateInX, rotateInY);
    result = matrixMultiplication(translate, result);
    result = matrixMultiplication(ortho, result);

    // instead of applying matrices one at the time, apply result at once to all points
    cube.matrixOperation(result);

    // draw lines between points and display result
    cube.drawCube();

    return 0;
}
