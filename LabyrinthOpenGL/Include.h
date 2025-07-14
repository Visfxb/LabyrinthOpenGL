#pragma once
#include <GL/glew.h>
#include <Windows.h>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <chrono>
#include <fstream>
#include "WindowContext.h"
#include "List.h"

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

#define debugLines

using namespace std;
using namespace chrono;

const float PI = 3.1415926;
const int alpha = 65;

const int windowWidth = 1600;
const int windowHeigth = 800;

const float blockWidth = float(45 * 0.75);
const float blockHeigth = float(95 * 0.75 * cos(alpha * PI / 180));
const float blockDepth = float(50 * 0.75 * sin(alpha * PI / 180));