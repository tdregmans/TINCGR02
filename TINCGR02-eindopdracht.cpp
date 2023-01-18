/*
    TINCGR02-eindopdracht.cpp

    version 8 (final version)

    CMI-TI 22 TINCGR02
    Student: Thijs Dregmans (1024272)
    Eindopdracht (Inleveropdracht)
    Last edited: 12-01-2023

    The assignment didn't provide a template. I used a standard OpenGL C++ template.
    I have chosen to program this assignment using C++, because
    I want to learn more about C++.

    Requirements
        -   The application must run without errors.
        -   The application uses a number of the following:
            -   Polygonen
            -   3D-vormen (massief)
            -   krommen
            -   animatie
            -   gebruikersinterface
            -   3D transformaties
            -   perspectief
            -   belichting
            -   shading
            -   texture mapping
            -   shaders



    Tests
        I test the application by checking all requirements.
        The first requirement are easy to check.
        The other requirement, I check in this way:
        1.  I go through all the points that can be awarded. I check whether
            I have 6 or more points. If I do, this test is
            finished successfully.

    Design
        This assignment, we need to use a number of items from the list.
        I choose to use:
        -   Polygons
        -   3D-shapes
        -   Animations
        -   User input
        -   3D-transformations
        -   Lightning

        If I used a resource for building a function, I will
        put the URL in the code.

*/

// Include OpenGL libs
#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>

// Include standard lib
#include <stdlib.h>

// Include Windows lib, for Sleep(unsigned seconds) function
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

// Define constants
const float SPEED = 0.02;

const float startRotationInX = -20;
const float startRotationInY = 20;

// Define start values
float rotationInX = 0;
float rotationInY = 0;

// Display Cube with all dots
void displayCube() {

    // SolidCube
    glutSetColor(1, 0.0, 0.0, 0.0);
    glutSolidCube(1);

    // Dept test
    glEnable(GL_DEPTH_TEST);

    // Set color for dots on cube
    glColor3f(0.0f, 0.0f, 0.0f);

    // Dot 1.1
    glBegin(GL_POLYGON);
    glVertex3f(0.05, 0.05, 0.51); // P1
    glVertex3f(-0.05, 0.05, 0.51); // P2
    glVertex3f(-0.05, -0.05, 0.51); // P3
    glVertex3f(0.05, -0.05, 0.51); // P4
    glEnd();

    // Dot 6.1
    glBegin(GL_POLYGON);
    glVertex3f(0.05, 0.15, -0.51); // P1
    glVertex3f(-0.05, 0.15, -0.51); // P2
    glVertex3f(-0.05, 0.05, -0.51); // P3
    glVertex3f(0.05, 0.05, -0.51); // P4
    glEnd();
    // Dot 6.2
    glBegin(GL_POLYGON);
    glVertex3f(0.25, 0.15, -0.51); // P1
    glVertex3f(0.15, 0.15, -0.51); // P2
    glVertex3f(0.15, 0.05, -0.51); // P3
    glVertex3f(0.25, 0.05, -0.51); // P4
    glEnd();
    // Dot 6.3
    glBegin(GL_POLYGON);
    glVertex3f(-0.15, 0.15, -0.51); // P1
    glVertex3f(-0.25, 0.15, -0.51); // P2
    glVertex3f(-0.25, 0.05, -0.51); // P3
    glVertex3f(-0.15, 0.05, -0.51); // P4
    glEnd();
    // Dot 6.4
    glBegin(GL_POLYGON);
    glVertex3f(0.05, -0.05, -0.51); // P1
    glVertex3f(-0.05, -0.05, -0.51); // P2
    glVertex3f(-0.05, -0.15, -0.51); // P3
    glVertex3f(0.05, -0.15, -0.51); // P4
    glEnd();
    // Dot 6.5
    glBegin(GL_POLYGON);
    glVertex3f(0.25, -0.05, -0.51); // P1
    glVertex3f(0.15, -0.05, -0.51); // P2
    glVertex3f(0.15, -0.15, -0.51); // P3
    glVertex3f(0.25, -0.15, -0.51); // P4
    glEnd();
    // Dot 6.6
    glBegin(GL_POLYGON);
    glVertex3f(-0.15, -0.05, -0.51); // P1
    glVertex3f(-0.25, -0.05, -0.51); // P2
    glVertex3f(-0.25, -0.15, -0.51); // P3
    glVertex3f(-0.15, -0.15, -0.51); // P4
    glEnd();

    // Dot 3.1
    glBegin(GL_POLYGON);
    glVertex3f(-0.51, 0.05, -0.05); // P1
    glVertex3f(-0.51, 0.05, 0.05); // P2
    glVertex3f(-0.51, -0.05, 0.05); // P3
    glVertex3f(-0.51, -0.05, -0.05); // P4
    glEnd();
    // Dot 3.2
    glBegin(GL_POLYGON);
    glVertex3f(-0.51, 0.25, 0.15); // P1
    glVertex3f(-0.51, 0.25, 0.25); // P2
    glVertex3f(-0.51, 0.15, 0.25); // P3
    glVertex3f(-0.51, 0.15, 0.15); // P4
    glEnd();
    // Dot 3.3
    glBegin(GL_POLYGON);
    glVertex3f(-0.51, -0.15, -0.25); // P1
    glVertex3f(-0.51, -0.15, -0.15); // P2
    glVertex3f(-0.51, -0.25, -0.15); // P3
    glVertex3f(-0.51, -0.25, -0.25); // P4
    glEnd();

    // Dot 4.1
    glBegin(GL_POLYGON);
    glVertex3f(0.51, 0.25, 0.15); // P1
    glVertex3f(0.51, 0.25, 0.25); // P2
    glVertex3f(0.51, 0.15, 0.25); // P3
    glVertex3f(0.51, 0.15, 0.15); // P4
    glEnd();
    // Dot 4.2
    glBegin(GL_POLYGON);
    glVertex3f(0.51, -0.15, -0.25); // P1
    glVertex3f(0.51, -0.15, -0.15); // P2
    glVertex3f(0.51, -0.25, -0.15); // P3
    glVertex3f(0.51, -0.25, -0.25); // P4
    glEnd();
    // Dot 4.3
    glBegin(GL_POLYGON);
    glVertex3f(0.51, -0.25, 0.15); // P1
    glVertex3f(0.51, -0.25, 0.25); // P2
    glVertex3f(0.51, -0.15, 0.25); // P3
    glVertex3f(0.51, -0.15, 0.15); // P4
    glEnd();
    // Dot 4.4
    glBegin(GL_POLYGON);
    glVertex3f(0.51, 0.25, -0.15); // P1
    glVertex3f(0.51, 0.25, -0.25); // P2
    glVertex3f(0.51, 0.15, -0.25); // P3
    glVertex3f(0.51, 0.15, -0.15); // P4
    glEnd();

    // Dot 2.1
    glBegin(GL_POLYGON);
    glVertex3f(0.25, 0.51, 0.15); // P1
    glVertex3f(0.25, 0.51, 0.25); // P2
    glVertex3f(0.15, 0.51, 0.25); // P3
    glVertex3f(0.15, 0.51, 0.15); // P4
    glEnd();
    // Dot 2.2
    glBegin(GL_POLYGON);
    glVertex3f(-0.25, 0.51, -0.15); // P1
    glVertex3f(-0.25, 0.51, -0.25); // P2
    glVertex3f(-0.15, 0.51, -0.25); // P3
    glVertex3f(-0.15, 0.51, -0.15); // P4
    glEnd();

    // Dot 5.1
    glBegin(GL_POLYGON);
    glVertex3f(0.05, -0.51, -0.05); // P1
    glVertex3f(0.05, -0.51, 0.05); // P2
    glVertex3f(-0.05, -0.51, 0.05); // P3
    glVertex3f(-0.05, -0.51, -0.05); // P4
    glEnd();
    // Dot 5.2
    glBegin(GL_POLYGON);
    glVertex3f(0.25, -0.51, 0.15); // P1
    glVertex3f(0.25, -0.51, 0.25); // P2
    glVertex3f(0.15, -0.51, 0.25); // P3
    glVertex3f(0.15, -0.51, 0.15); // P4
    glEnd();
    // Dot 5.3
    glBegin(GL_POLYGON);
    glVertex3f(-0.25, -0.51, -0.15); // P1
    glVertex3f(-0.25, -0.51, -0.25); // P2
    glVertex3f(-0.15, -0.51, -0.25); // P3
    glVertex3f(-0.15, -0.51, -0.15); // P4
    glEnd();
    // Dot 5.4
    glBegin(GL_POLYGON);
    glVertex3f(0.25, -0.51, -0.15); // P1
    glVertex3f(0.25, -0.51, -0.25); // P2
    glVertex3f(0.15, -0.51, -0.25); // P3
    glVertex3f(0.15, -0.51, -0.15); // P4
    glEnd();
    // Dot 5.5
    glBegin(GL_POLYGON);
    glVertex3f(-0.25, -0.51, 0.15); // P1
    glVertex3f(-0.25, -0.51, 0.25); // P2
    glVertex3f(-0.15, -0.51, 0.25); // P3
    glVertex3f(-0.15, -0.51, 0.15); // P4
    glEnd();

    // Reset color
    glColor3f(1.0, 1.0, 1.0);
}

// Standard Display function cube and rotate to show sides
void display() {
    // Clear screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();

    // Rotate cube to show sides
    glRotatef(startRotationInX, 1, 0, 0);
    glRotatef(startRotationInY, 0, 1, 0);

    // Display Cube with dots
    displayCube();

    glPopMatrix();
    glutSwapBuffers();
}

// Display cube with a animations
void displayAnimation() {
    // Clear screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();

    // Display Cube with dots
    displayCube();

    glPopMatrix();
    glutSwapBuffers();
}

// Update the screen when a key is pressed
void update(unsigned char key, int x, int y) {

    // SPACE-key
    if (key == 32) {
        // Clear screen
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glPushMatrix();

        glRotatef(startRotationInX, 1, 0, 0);
        glRotatef(startRotationInY, 0, 1, 0);

        // Generate random numbers for rotations
        int newRotationsInX = (std::rand() % 6);
        int newRotationsInY = (std::rand() % 6);

        // For each rotation
        for(int xRotations = 0; xRotations < newRotationsInX; xRotations++) {
            // For each degree in rotation
            for(int xDegrees = 0; xDegrees < 90; xDegrees++) {
                // Rotate cube 1 degree
                glRotatef(1, 1, 0, 0);
                // Sleep 2 ms
                Sleep(2);
                // Display cube
                displayAnimation();
            }
        }

        // For each rotation
        for(int yRotations = 0; yRotations < newRotationsInY; yRotations++) {
            // For each degree in rotation
            for(int yDegrees = 0; yDegrees < 90; yDegrees++) {
                // Rotate cube 1 degree
                glRotatef(1, 0, 1, 0);
                // Sleep 2 ms
                Sleep(2);
                // Display cube
                displayAnimation();
            }
        }

        glPopMatrix();
        glutSwapBuffers();
    }


    // Kill screen, when ESC-key is pressed
    if (key == 27) {
        std::exit(1);
    }
}

int main(int argc, char **argv) {
    // Init settings
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutCreateWindow("TINCGR02-eindopdracht");

    // Remove lighting
    glDisable(GL_LIGHT0);
    glDisable(GL_LIGHT1);

    // Add new light
    float light_diffuse[] = {1.0, 1.0, 1.0, 1.0};
    float light_position[] = {1.0, 1.0, -1.0, 0.0};

    glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);

    glLightf(GL_LIGHT0, GL_DIFFUSE, GL_SPOT_EXPONENT);

    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);

    // Set default color for cube and dots
    glColor3f(1.0, 1.0, 1.0);

    // Set Frustum
    glFrustum(1.333, -1.333, 1, -1, -2, 20);

    // Add functions to events
    glutDisplayFunc(display);
    glutKeyboardFunc(update);

    // Call display() so the cube is show when the screen starts
    display();

    glutMainLoop();
    return 0;
}
