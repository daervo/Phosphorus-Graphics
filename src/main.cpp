#include "../headers/SuperHeader.h"
#include "../headers/Enable.h"
#include "../headers/Draw.h"
#include "../headers/Disable.h"
#include "../headers/meshLoader.h"
#include "../headers/Textures.h"
#include "../headers/camera.h"
#include "../headers/mat4.h"
#include "../headers/vector3d.h"
#include <fstream>

LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);
void setScreenSize();

GLuint WINWIDTH = 600;
GLuint WINHEIGHT = 600;

GLuint WINLOCKX = 0;
GLuint WINLOCKY = 0;

GLboolean debugMode = GL_FALSE;

GLboolean bQuit = GL_FALSE;

std::vector<meshLoader*> scenes;
mat4* viewMatrix = new mat4();
vector3d position(0.0, 0.0, 0.0);
vector3d scenePosition(0.0, 0.0, 0.0);
Camera* camera = new Camera();
vector3d lookUp(1,0,0);
vector3d lookLeft(0,1,0);
GLfloat x = 0;
GLfloat y = 0;

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
    scenes.push_back(new meshLoader("C:\\Users\\Ervin\\workspace2\\Phosphorus-Graphics\\Peugeot 207\\Peugeot_207.3DS"));
    scenes.push_back(new meshLoader("C:\\Users\\Ervin\\workspace2\\Phosphorus-Graphics\\Peugeot 207\\Peugeot_207.3DS"));
	//textures* tex= new textures(scene->getScene(), scene->getPath());
	//tex->bindTextures("C:\\Users\\Ervin\\workspace2\\Phosphorus-Graphics\\Peugeot 207\\Texture\\");
    std::map<std::string, GLuint*> texMap;// = tex->getTextureIdMap();
    camera->setPosition(0.0, 0.0, 5.0);

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
        drawHandle(hDC, scenes, texMap, camera, &position);
    }

    /* shutdown OpenGL */
    disableOpenGL(hwnd, hDC, hRC);

    /* destroy the window explicitly */
    DestroyWindow(hwnd);

    return msg.wParam;
}
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	float velocity = 0.5;
	vector3d newPosition;
	//GLfloat newForward;
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
                case VK_UP://move towards lookat
                	cout<<"current position is "<<camera->getPosition()->x <<" "<<camera->getPosition()->y <<" " << camera->getPosition()->z<<endl;
                	newPosition = ((*camera->getPosition()) - (*camera->getForward()));
                	newPosition.normalize();
                	cout<<"normalized is "<<newPosition.x <<" "<<newPosition.y <<" " << newPosition.z<<endl;
                	camera->setPosition(camera->getPosition()->x - (velocity*newPosition.x),
                			camera->getPosition()->y - (velocity*newPosition.y),
                			camera->getPosition()->z - (velocity*newPosition.z));
                	cout<<"new position is "<<camera->getPosition()->x <<" "<<camera->getPosition()->y <<" " << camera->getPosition()->z<<endl;
                break;
                case VK_DOWN://move away from lookat
                	cout<<"current position is "<<camera->getPosition()->x <<" "<<camera->getPosition()->y <<" " << camera->getPosition()->z<<endl;
                	                	newPosition = ((*camera->getPosition()) - (*camera->getForward()));
                	                	newPosition.normalize();
                	                	cout<<"normalized is "<<newPosition.x <<" "<<newPosition.y <<" " << newPosition.z<<endl;
                	                	camera->setPosition(camera->getPosition()->x + (velocity*newPosition.x),
                	                			camera->getPosition()->y + (velocity*newPosition.y),
                	                			camera->getPosition()->z + (velocity*newPosition.z));
                	                	cout<<"new position is "<<camera->getPosition()->x <<" "<<camera->getPosition()->y <<" " << camera->getPosition()->z<<endl;
                break;
                case VK_RIGHT:
                	//viewMatrix->turnRight(velocity);
                	//viewMatrix->addForward(0.1, 0.0, 0.0);
                break;
                case VK_LEFT:
                	//viewMatrix->turnRight(-velocity);
                	//viewMatrix->addForward(-0.1, 0.0, 0.0);
                break;
                case VK_NUMPAD8:
                	cout<<"current look at is x:"<<camera->getForward()->x
                	<<" y:"<<camera->getForward()->y <<" z:" << camera->getForward()->z<<endl;
                	lookUp.x-=velocity;
                	camera->anglesToAxes(lookUp);
                	cout<<"look at is now x:"<<camera->getForward()->x
                	<<" y:"<<camera->getForward()->y <<" z:" << camera->getForward()->z<<endl;
                	cout<<"new position is "<<camera->getPosition()->x <<" "<<camera->getPosition()->y <<" " << camera->getPosition()->z<<endl;
                	cout<<"new up is "<<camera->getUp()->x <<" "<<camera->getUp()->y <<" " << camera->getUp()->z<<endl;

                	cout<<"new right is "<<camera->getLeft()->x <<" "<<camera->getLeft()->y <<" " << camera->getLeft()->z<<endl;
                break;
                case VK_NUMPAD5:
                	lookUp.z-=velocity;
                	camera->anglesToAxes(lookUp);
                	cout<<"current look at is  x:"<<camera->getForward()->x
                	<<" y:"<<camera->getForward()->y <<" z:" << camera->getForward()->z<<endl;
                break;
                case VK_NUMPAD4:
                	lookLeft.y += velocity;
                	camera->anglesToAxes(lookLeft);
                	cout<<"current look at is  x:"<<camera->getForward()->x
                	<<" y:"<<camera->getForward()->y <<" z:" << camera->getForward()->z<<endl;
                break;
                case VK_NUMPAD6:
                	lookLeft.y -= velocity;
                	camera->anglesToAxes(lookLeft);
                	cout<<"current look at is  x:"<<camera->getForward()->x
                	<<" y:"<<camera->getForward()->y <<" z:" << camera->getForward()->z<<endl;
                break;
                case VK_SPACE:
                	glm::vec2 mousePos(++x, ++y);
                	viewMatrix->mouseUpdate(mousePos);
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
