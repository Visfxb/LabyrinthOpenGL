#include "Menu/MainScene.h"
#include "Game/GameScene.h"
#include "Menu/PauseScene.h"
#include "Menu/LogInScene.h"
#include "Menu/SignUpScene.h"


int findMaxId(string profilesName) {
	ifstream profiles(profilesName);
	Profile bufProfile = Profile();
	int maxId = 0;
	while (true) {
		Profile p;
		p.loadFromFile(profiles);
		if (profiles.eof()) break;
		if (p.getId() > maxId)
			maxId = p.getId();
	}

	return maxId;
}

string profiles = "profile.txt";
int Profile::id = findMaxId(profiles) + 1;


LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);

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
	wcex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);


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
		24,
		0,
		0,
		0,
		FW_NORMAL,
		FALSE,
		FALSE,
		FALSE,
		ANSI_CHARSET,
		OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY,
		FF_DONTCARE | DEFAULT_PITCH,
		L"Consolas"
	);

	WindowContext::getInstance().setWindow(hwnd, hDC, hRC);
	SelectObject(hDC, hFont);
	GLuint base = glGenLists(256);
	wglUseFontBitmaps(hDC, 0, 256, base);
	WindowContext::getInstance().setFont(hFont, base);




	srand(time(0));
	
	ifstream mapTxt("map.txt");
	Map map(mapTxt);
	Entities::Fighters::Player player(38, 1, 0.3f, map, 50);
	Entities::Items::Coin coin(map, 1, 1);

	Scene* mainScene = new MainScene();
	Scene* gameScene = new GameScene(map, player);
	Scene* pauseScene = new PauseScene(gameScene);
	Scene* logInScene = new LogInScene(profiles);
	Scene* signUpScene = new SignUpScene(profiles);

	mainScene->addNewButton(new Buttons::Button(50, 100, 200, 50, "Game", gameScene));
	mainScene->addNewButton(new Buttons::Button(300, 100, 200, 50, "Log in", logInScene));

	gameScene->addNewButton(new Buttons::Button(10, 10, 50, 50, "||", pauseScene));
	
	pauseScene->addNewButton(new Buttons::Button(100, 100, 200, 50, "To main", mainScene));
	pauseScene->addNewButton(new Buttons::Button(100, 200, 200, 50, "To game", gameScene));
	
	logInScene->addNewButton(new Buttons::Button(100, 100, 200, 50, "Back", mainScene));
	logInScene->addNewButton(new Buttons::Button(100, 200, 200, 50, "Sign up", signUpScene));
	logInScene->addNewButton(new Buttons::InputField(400, 300, 300, 50, "Enter Nickname ...", "nickname"));
	logInScene->addNewButton(new Buttons::InputField(400, 200, 300, 50, "Enter Password ...", "password"));
	logInScene->addNewButton(new Buttons::Button(450, 100, 200, 50, "Log in", logInScene));
	
	signUpScene->addNewButton(new Buttons::Button(100, 100, 200, 50, "Back", logInScene));
	signUpScene->addNewButton(new Buttons::InputField(400, 400, 300, 50, "Enter Nickname ...", "nickname"));
	signUpScene->addNewButton(new Buttons::InputField(400, 300, 300, 50, "Enter Password ...", "password"));
	signUpScene->addNewButton(new Buttons::InputField(400, 200, 300, 50, "Confirm Password ...", "confirm password"));
	signUpScene->addNewButton(new Buttons::Button(450, 100, 200, 50, "Save", signUpScene));

	Scene* currentScene = mainScene;
	Scene* newScene = currentScene;

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
			glOrtho(0, WindowContext::getInstance().getWidth(), 0, WindowContext::getInstance().getHeight(), -1, 1);
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();


			POINT mouse = getMouseXY(hwnd);
			currentScene->update(mouse.x, mouse.y);
			currentScene->handleInput();
			newScene = currentScene->getNextScene();
			currentScene->resetNextScene();
			
			if (newScene != nullptr && currentScene != newScene)
				currentScene = newScene;
			currentScene->draw();


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
	WindowContext::getInstance().setLastMessage(uMsg, wParam, lParam);
	switch (uMsg)
	{
	case WM_CLOSE:
		PostQuitMessage(0);
		break;

	case WM_SIZE:
		WindowContext::getInstance().updateSize();
		break;

	case WM_DESTROY:
		return 0;

	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}

	return 0;
}
