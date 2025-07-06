#include "Player.h"
#include "Coin.h"
#include "Map.h"

void glPrintText(float x, float y, const char* text, HDC hDC, GLuint base)
{
	glRasterPos2f(x, y);
	glColor3f(0, 0, 0);
	glListBase(base);
	glCallLists(strlen(text), GL_UNSIGNED_BYTE, text);
}





LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);
void EnableOpenGL(HWND hwnd, HDC*, HGLRC*);
void DisableOpenGL(HWND, HDC, HGLRC);


int WINAPI WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nCmdShow)
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

	HFONT hFont = CreateFont(
		24,                // высота шрифта
		0,                 // ширина
		0,                 // угол наклона
		0,                 // ориентация
		FW_NORMAL,         // толщина
		FALSE,             // курсив
		FALSE,             // подчеркивание
		FALSE,             // зачёркивание
		ANSI_CHARSET,      // набор символов
		OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY,
		FF_DONTCARE | DEFAULT_PITCH,
		L"Consolas"        // имя шрифта
	);
	SelectObject(hDC, hFont);
	GLuint base = glGenLists(256); // 256 символов
	wglUseFontBitmaps(hDC, 0, 256, base);



	srand(time(0));
	Map map({
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
		});
	Entities::Fighters::Player test(38, 1, 0.3f, map);
	auto lastInputTick = high_resolution_clock::now();
	const int delay = 1000 / 10;
	Entities::Items::Coin coin(map, 36, 1);

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

			auto now = high_resolution_clock::now();
			auto ms = duration_cast<milliseconds>(now - lastInputTick).count();
			if (ms >= delay)
			{
				if (GetKeyState('W') < 0) test.movePlayer(map, coin, -1);
				if (GetKeyState('A') < 0) test.movePlayer(map, coin, -2);
				if (GetKeyState('S') < 0) test.movePlayer(map, coin, 1);
				if (GetKeyState('D') < 0) test.movePlayer(map, coin, 2);
				lastInputTick = now;
			}
			glTranslatef(50, 200, 0);
			map.paintMap(test, coin);


			glColor3f(0, 0, 0);
			glPrintText(0, -50, to_string(test.getX() + test.getInBlockX()).c_str(), hDC, base);
			glPrintText(0, -100, to_string(test.getY() + test.getInBlockY()).c_str(), hDC, base);
			glPrintText(0, -150, to_string(test.getCoins()).c_str(), hDC, base);

			SwapBuffers(hDC);
			Sleep(10);
		}
	}
	DisableOpenGL(hwnd, hDC, hRC);
	DestroyWindow(hwnd);
	glDeleteLists(base, 256);
	DeleteObject(hFont);

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