/*
    TINCGR02-opdracht3.cpp

    version 1
    
    CMI-TI 22 TINCGR02
    Student: Thijs Dregmans (1024272)
    Inleveropdracht 2
    Last edited: 21-11-2022

    The assignment provides the template that I used.
    I have chosen to program this assignment using C++, because
    I want to learn more about C++.

    Requirements
        -   The application must run without errors.
        -   The application correctly implements the directions: 0° and 180°.
        -   The application correctly implements the directions: 90° and 270°.
        -   The application correctly implements the directions between: -45° and 45°.
        -   The application correctly implements the directions between: 135° and 225°.
        -   The application correctly implements the directions between: 45° and 135°.
        -   The application correctly implements the directions between: 255° and 315°.
        -   All lines are long enough.
        -   Anti-aliasing is used.

    
    Tests
        I test the application by checking all requirements.
        The first requirements is easy to check.
        The other requirements, I check in this way:
        1.  I will take 15 directions between 0° and 359°.
            For each I will run the application and check if a line is drawn.
            If a line is drawn, I use a ruler to see if the angle is correct.
            If all 15 angles are correct, the test is done.
        2.  All lines must be long enough. They must go on to the end of the screen.
        3.  Anti-aliasing is a bonus.
            
    
    Design
        I use the template provided in the assignment:
        'rastering.cpp'

        If I used a resource for building a function, I will
        put the url in the code.

        
    
*/




// Compileren:
//
// Op MacOS:
// c++ -std=c++11 -o rastering -framework OpenGL -framework GLUT rastering.cpp
//
// Op Linux en Windows:
// g++ -std=c++11 -o rastering rastering.cpp -l GL -l glut

#include <list>

#define GL_SILENCE_DEPRECATION
#include <GL/gl.h>
#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif

#define GRID_SIZE 10

using namespace std;

class Point {
    public:
        int x, y;
        Point(int, int);
};

Point::Point(int x, int y) {
    this->x = x;
    this->y = y;
}

class Grid {
    int sizeX, sizeY;
    list<Point> points;
    public:
        Grid(int, int);
        void addPoint(int, int);
        void rasterline(int, int, int, int);
        void draw();
        void display();
};

Grid *currentInstance;

void display() {
    currentInstance->display();
}

void end(unsigned char key, int x, int y) {
    exit(0);
}

Grid::Grid(int x, int y) {
    sizeX = x;
    sizeY = y;
}

void Grid::display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1, 1, 1);
    for (auto &point: points) {
        glRecti(point.x * GRID_SIZE, point.y * GRID_SIZE, (point.x + 1) * GRID_SIZE, (point.y + 1) * GRID_SIZE);
    }
    glColor3f(.5, .5, .5);
    glBegin(GL_LINES);
    for (int i = 1; i < sizeX; i++) {
        glVertex2f(i * GRID_SIZE, 0);
        glVertex2f(i * GRID_SIZE, sizeY * GRID_SIZE);
    }
    for (int i = 1; i < sizeY; i++) {
        glVertex2f(0, i * GRID_SIZE);
        glVertex2f(sizeX * GRID_SIZE, i * GRID_SIZE);
    }
    glEnd();
    glFlush();
}

void Grid::draw() {
    int argc = 0;
    glutInit(&argc, NULL);
    glutInitDisplayMode(GLUT_RGBA);
    glutInitWindowSize(sizeX * GRID_SIZE, sizeY * GRID_SIZE);
    glutCreateWindow("Raster");
    glOrtho(0, sizeX * GRID_SIZE, sizeY * GRID_SIZE, 0, -1, 1);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    currentInstance = this;
    glutDisplayFunc(::display); // Cannot use instance function here, so must use function in global namespace
    glutKeyboardFunc(end);
    glutMainLoop();
}

void Grid::addPoint(int x, int y) {
    if (x < sizeX && y < sizeY && x >= 0 && y >= 0) {
        points.emplace_back(x, y);
    }
}

void Grid::rasterline(int x0, int y0, int x1, int y1) {
    // to do
}

int main() {
    // testcode
    // let op: de beoordeling wordt gedaan op basis van andere waarden
    Grid grid(20, 20);
    grid.rasterline(0, 0, 19, 19);
    grid.rasterline(0, 10, 19, 0);
    grid.draw();
    return 0; // never reached
}