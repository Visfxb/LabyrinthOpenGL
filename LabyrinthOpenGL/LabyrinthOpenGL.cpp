//#include <GLFW/glfw3.h>
#include <GL/glew.h>
#include <Windows.h>
#include <iostream>
#include <vector>
#include <cmath>
#include <string>

//#pragma comment (lib, "glfw32.lib")
#pragma comment (lib, "opengl32.lib")
#pragma comment (lib, "glew32.lib")
#pragma comment (lib, "User32.lib")
#pragma comment (lib, "Gdi32.lib")
using namespace std;

//linker
//opengl32.lib
//glew32.lib
//glfw3.lib
//User32.lib
//Gdi32.lib
//SUBSYSTEM:WINDOWS



const float PI = 3.1415;
int alpha = 65;

const int windowWidth = 2200;
const int windowHeigth = 900;

const float blockWidth = 50;
const float blockHeigth = 90 * cos(alpha * PI / 180);
const float blockDepth = 50 * sin(alpha * PI / 180);

const vector<string> map = {
        "########################################",
        "#    #         #                       #",
        "#  ###         #                       #",
        "#    #    #    ######    ##########    #",
        "###  #    #    #         #        #    #",
        "#    #    #              #   #    #    #",
        "#  ###    #              #   ###########",
        "#    #    #########      #        #    #",
        "###  #            #      #        #    #",
        "#    #            #      #####    #    #",
        "#  ###    ####    #                    #",
        "#    #       #    #                    #",
        "#    #       #    #######   #          #",
        "#    #########    #         #          #",
        "#                 #         #          #",
        "########################################"
};


void paintWall() {
    glBegin(GL_TRIANGLE_STRIP);
        glColor3f(0.2, 0.2, 0.2);
        glVertex2f(0, 0);
        glVertex2f(blockWidth, 0);
        glVertex2f(0, blockHeigth);
        glVertex2f(blockWidth, blockHeigth);
    glEnd();
    glTranslatef(0, blockHeigth, 0);

    glBegin(GL_TRIANGLE_STRIP);
        glColor3f(0.5, 0.5, 0.5);
        glVertex2f(0, 0);
        glVertex2f(blockWidth, 0);
        glVertex2f(0, blockDepth);
        glVertex2f(blockWidth, blockDepth);
    glEnd();
    glTranslatef(0, -blockHeigth, 0);
}


void paintMap(const vector<string> map) {
    glPushMatrix();
    glTranslatef(50, windowHeigth - blockHeigth - blockDepth - 50, 0);

    for (int i = 0; i < map.size(); i++)
    {
        for (int j = 0; j < map[i].size(); j++)
        {
            if (map[i][j] == '#')
                paintWall();
            glTranslatef(blockWidth, 0, 0);
        }
        glTranslatef(map[i].size() * -blockWidth, -blockDepth, 0);
    }
    glPopMatrix();
}


void GetMousePos(HWND hwnd, int& x, int& y)
{
    POINT pt;
    if (GetCursorPos(&pt)) {
        ScreenToClient(hwnd, &pt);
        x = pt.x;
        y = pt.y;
    }
    else
        x = y = 0;
}


LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);
void EnableOpenGL(HWND hwnd, HDC*, HGLRC*);
void DisableOpenGL(HWND, HDC, HGLRC);


int WINAPI WinMain(HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR lpCmdLine,
    int nCmdShow)
{
    WNDCLASSEX wcex;
    HWND hwnd;
    HDC hDC;
    HGLRC hRC;
    MSG msg;
    BOOL bQuit = FALSE;
    float theta = 0.0f;

    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_OWNDC;
    wcex.lpfnWndProc = WindowProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = L"GLSample";
    wcex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);;


    if (!RegisterClassEx(&wcex))
        return 0;

    //create main window
    hwnd = CreateWindowEx(0,
        L"GLSample",
        L"OpenGL Sample",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        windowWidth,
        windowHeigth,
        NULL,
        NULL,
        hInstance,
        NULL);

    ShowWindow(hwnd, nCmdShow);
    EnableOpenGL(hwnd, &hDC, &hRC);

    while (!bQuit)
    {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
                bQuit = TRUE;
            else
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
        else
        {
            glClearColor(0.7f, 1.0f, 0.7f, 0.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            glOrtho(0, windowWidth, 0, windowHeigth, -1, 1);
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();


            paintMap(map);


            SwapBuffers(hDC);
            Sleep(1);
        }
    }
    DisableOpenGL(hwnd, hDC, hRC);
    DestroyWindow(hwnd);

    return msg.wParam;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_CLOSE:
        PostQuitMessage(0);
        break;

    case WM_DESTROY:
        return 0;

    case WM_KEYDOWN:
    {
        switch (wParam)
        {
        case VK_ESCAPE:
            PostQuitMessage(0);
            break;
        }
    }

    case WM_LBUTTONDOWN:
    {

        break;
    }

    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }

    return 0;
}

void EnableOpenGL(HWND hwnd, HDC* hDC, HGLRC* hRC)
{
    PIXELFORMATDESCRIPTOR pfd;
    int iFormat;
    *hDC = GetDC(hwnd);
    ZeroMemory(&pfd, sizeof(pfd));
    pfd.nSize = sizeof(pfd);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW |
        PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 24;
    pfd.cDepthBits = 16;
    pfd.iLayerType = PFD_MAIN_PLANE;
    iFormat = ChoosePixelFormat(*hDC, &pfd);
    SetPixelFormat(*hDC, iFormat, &pfd);
    *hRC = wglCreateContext(*hDC);
    wglMakeCurrent(*hDC, *hRC);
}

void DisableOpenGL(HWND hwnd, HDC hDC, HGLRC hRC)
{
    wglMakeCurrent(NULL, NULL);
    wglDeleteContext(hRC);
    ReleaseDC(hwnd, hDC);
}