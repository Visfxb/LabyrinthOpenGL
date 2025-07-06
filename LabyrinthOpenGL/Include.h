#pragma once
//#include <GLFW/glfw3.h>
#include <GL/glew.h>
#include <Windows.h>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <chrono>

//#pragma comment (lib, "glfw32.lib")

struct paintSettings
{
    int vec;
    float visiblePart;

    paintSettings(int vec, float visiblePart) {
        this->vec = vec;
        this->visiblePart = visiblePart;
    }
};
struct rgb
{
    float red;
    float green;
    float blue;

    rgb(float r, float g, float b) {
        red = r;
        green = g;
        blue = b;
    }
};

#define debugLinesf

using namespace std;
using namespace chrono;

const float PI = 3.1415926;
const int alpha = 65;

const int windowWidth = 2200;
const int windowHeigth = 900;

const float blockWidth = 60 * 0.75;
const float blockHeigth = 90 * 0.75 * cos(alpha * PI / 180);
const float blockDepth = 50 * 0.75 * sin(alpha * PI / 180);