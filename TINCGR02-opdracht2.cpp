/*
    TINCGR02-opdracht2.cpp

    version 2 (final version)
    
    CMI-TI 22 TINCGR02
    Student: Thijs Dregmans (1024272)
    Inleveropdracht 2
    Last edited: 19-11-2022

    The assignment provides the template that I used.
    I have chosen to program this assignment using C++, because
    I want to learn more about C++.

    Requirements
        -   The application must run without errors.
        -   The application correctly implements RGBtoCMY()
        -   The application correctly implements CMYtoRGB()
        -   The application correctly implements RGBtoHSL()
        -   The application correctly implements HSLtoRGB()
        -   The application correctly implements transparency()
        -   The application contains helpful comments.
    
    Tests
        I test the application by checking all requirements.
        The first and last requirements are easy to check.
        The other requirements, I check in two ways:
        1.  The template provides example colors and their outcomes.
            I will use these colors and check if the outcomes
            match the console output.
        2.  For each function, I will take 5 random colors
            and use these as input. I will take the input into
            a online calculator. If the outputs match, the
            function must be correctly implemented. If the
            application fails, there must be an error.
    
    Design
        I use the template provided in the assignment:
        'colorspace.cpp'

        If I used a resource for building a function, I will
        put the url in the code.
    
*/

#include <iostream>
#include <string>
#include <cmath>

using namespace std;

// function for converting RGB to CMY
// parameters r, g and b must be between 0.0 and 1.0
float *RGBtoCMY(float r, float g, float b) {
    // source: http://www.huevaluechroma.com/092.php

    // r, g and b are the opposite of c, m and y
    float c = 1.0f - r;
    float m = 1.0f - g;
    float y = 1.0f - b;

    return new float[3] {c, m, y};
}

// function for converting CMY to RGB
// parameters c, m and y must be between 0.0 and 1.0
float *CMYtoRGB(float c, float m, float y) {
    // source: http://www.huevaluechroma.com/092.php

    // c, m and y are the opposite of r, g and b
    float r = 1.0f - c;
    float g = 1.0f - m;
    float b = 1.0f - y;

    return new float[3] {r, g, b};
}

// function for converting RGB to HSL
// parameters r, g and b must be between 0.0 and 1.0
float *RGBtoHSL(float r, float g, float b) {
    // source: https://en.wikipedia.org/wiki/HSL_and_HSV#General_approach

    // M is the max value, m is the minimal value and C is the range
    float M = max(r, max(g, b));
    float m = min(r, min(g, b));
    float C = M - m;

    // H', or Haccent, depends on M, m and C
    float Haccent;
    if (C == 0) {
        // undefined
        Haccent = 0;
    }
    else if (M == r) {
        Haccent = fmod(6, ((g - b) / C));
    }
    else if (M == g) {
        Haccent = ((b - r) / C) + 2;
    }
    else if (M == b) {
        Haccent = ((r - g) / C) + 4;
    }

    // calculate h, s and l
    float h = Haccent * 60;

    float l =  0.5 * (M + m); 
    
    // s depends on l
    float s;
    if (l == 0 || l == 1) {
        s = 0;
    }
    else {
        s = C / (1 - abs(2 * l - 1));
    }
    // calculated not in HSL order, but in HLS because L impacts S

    return new float[3] {h, s, l};
}

// function for converting HSL to RGB
// parameters h must be between 0 and 100
// parameters s and l must be between 0.0 and 1.0
float *HSLtoRGB(float h, float s, float l) {
    // source: https://en.wikipedia.org/wiki/HSL_and_HSV#HSL_to_RGB

    float C = (1 - abs(2 * l - 1)) * s;

    float Haccent = h / 60;
    float X = C *(1 - abs(fmod(2, Haccent) - 1));

    // R, G and B depends on Haccent
    float R;
    float G;
    float B;
    if (0 <= Haccent && Haccent < 1) {
        R = C;
        G = X;
        B = 0;
    }
    else if (1 <= Haccent && Haccent < 2) {
        R = X;
        G = C;
        B = 0;
    }
    else if (2 <= Haccent && Haccent < 3) {
        R = 0;
        G = C;
        B = X;
    }
    else if (3 <= Haccent && Haccent < 4) {
        R = 0;
        G = X;
        B = C;
    }
    else if (4 <= Haccent && Haccent < 5) {
        R = X;
        G = 0;
        B = C;
    }
    else if (5 <= Haccent && Haccent < 6) {
        R = C;
        G = 0;
        B = X;
    }
    
    float m = l - (C / 2);

    return new float[3] {R+m, G+m, B+m};
}

// function for calculating the result if to RGB colors are put on top of eachother and the first has a transparency
// parameters r1, g1, b1, alpha, r2, g2 and b2 must be between 0.0 and 1.0
float *transparency(float r1, float g1, float b1, float alpha, float r2, float g2, float b2) {
    // source: https://stackoverflow.com/questions/3506117/calculate-resulting-rgb-from-2-colors-one-is-transparent
    
    float r = r1 * alpha + r2 * (1 - alpha);
    float g = g1 * alpha + g2 * (1 - alpha);
    float b = b1 * alpha + b2 * (1 - alpha);

    return new float[3] {r, g, b};
}

// function for converting a color to a string that can be put in the console
string to_string(float *f) {
    return "(" + to_string(f[0]) + ", " + to_string(f[1]) + ", " + to_string(f[2]) + ")"; 
}

//
// main function
//
int main() {
    // testcode
    // let op: de beoordeling wordt gedaan op basis van andere waarden
    cout << to_string(RGBtoCMY(0.4, 0.5, 0.6)) << endl; // (0.6, 0.5, 0.4)
    cout << to_string(CMYtoRGB(0.4, 0.5, 0.6)) << endl; // (0.6, 0.5, 0.4)
    cout << to_string(RGBtoHSL(0.4, 0.5, 0.6)) << endl; // (210.0, 0.2, 0.5)
    cout << to_string(HSLtoRGB(100, 0.5, 0.6)) << endl; // (0.533, 0.8, 0.4)
    cout << to_string(transparency(0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0)) << endl; // (0.52, 0.62, 0.72)
    return 0;
}

// to run program:
    // g++ TINCGR02-opdracht2.cpp -o opdracht2.exe