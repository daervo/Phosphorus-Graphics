
#include "../headers/SuperHeader.h"
#include "../headers/Enable.h"
#include "../headers/Draw.h"
#include "../headers/Disable.h"
#include "../headers/meshLoader.h"
#include "../headers/Textures.h"
#include <fstream>

LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);
void setScreenSize();

GLuint WINWIDTH = 600;
GLuint WINHEIGHT = 600;

GLuint WINLOCKX = 0;
GLuint WINLOCKY = 0;

GLboolean debugMode = GL_FALSE;

GLboolean bQuit = GL_FALSE;

meshLoader* scene;

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

    /*string in = "";
    cout << "Run in normal mode? 'N' for debug mode..." << endl;
    cin >> in;
    if (in == "N"){
    	debugMode = GL_TRUE;
    }else{
    	cout << "Normal Mode" << endl;
    }*/

    /* register window class */
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_OWNDC;
    wcex.lpfnWndProc = WindowProc;
    wcex.cbClsExtra = WINLOCKX;
    wcex.cbWndExtra = WINLOCKY;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = "GLSample";
    wcex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);;


    if (!RegisterClassEx(&wcex))
        return 0;

    setScreenSize();

    /* create main window */
    hwnd = CreateWindowEx(0,
                          "GLSample",
                          "OpenGL Sample",
                          WS_POPUP,
                          0,
                          0,
                          WINWIDTH,
                          WINHEIGHT,
                          NULL,
                          NULL,
                          hInstance,
                          NULL);

    ShowWindow(hwnd, nCmdShow);

    /* enable OpenGL for the window */
    EnableOpenGL(hwnd, &hDC, &hRC);
    scene = new meshLoader("C:\\Users\\Ervin\\workspace2\\Phosphorus-Graphics\\Damaged Downtown\\Downtown_Damage_0.obj");
	//textures* tex= new textures(scene->getScene(), scene->getPath());
	//tex->bindTextures("C:\\Users\\Ervin\\workspace2\\Phosphorus-Graphics\\Peugeot 207\\Texture\\");
    std::map<std::string, GLuint*> texMap;// = tex->getTextureIdMap();

    /* program main loop */
    while (!bQuit)
    {
        /* check for messages */
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            /* handle dispatch message */
            TranslateMessage(&msg);
            DispatchMessage(&msg);

        }
          drawHandle(hDC, scene, texMap);
    }

    /* shutdown OpenGL */
    disableOpenGL(hwnd, hDC, hRC);

    /* destroy the window explicitly */
    DestroyWindow(hwnd);

    return msg.wParam;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
        case WM_DESTROY:
            return 0;

        case WM_KEYDOWN:
        {
            switch (wParam)
            {
                case VK_ESCAPE:
                    bQuit = GL_TRUE;
                break;
            }
        }
        break;

        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }

    return 0;
}

void setScreenSize(){
	HWND desktop = GetDesktopWindow();
	RECT screenSize;

	GetWindowRect(desktop, &screenSize);

	if (debugMode == GL_FALSE){
		WINWIDTH = screenSize.right;
		WINHEIGHT = screenSize.bottom;
	}


}

