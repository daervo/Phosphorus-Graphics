#include "../headers/SuperHeader.h"
#include "../headers/Enable.h"
#include "../headers/Draw.h"
#include "../headers/Disable.h"
#include "../headers/meshLoader.h"
#include "../headers/Textures.h"
#include "../headers/camera.h"
#include "../headers/mat4.h"
#include "../headers/vector3d.h"
#include <glm/glm.hpp>
#include <glm/gtx/rotate_vector.hpp>
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
Camera camera = Camera();
glm::vec3 lookUp(1,0,0);
vector3d lookDown(-1,0,0);
vector3d lookLeft(0,1,0);
vector3d lookRight(0,-1,0);
GLfloat x = 0;
GLfloat y = 0;
Camera testcam;

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
	camera.setPosition(0.0, 0.0, 5.0);
	camera.setUp(0.0, 1.0, 0.0);
	camera.setForward(0.0, 0.0, -1.0);
	camera.setLeft(1.0, 0.0, 0.0);
	testcam = Camera();
	testcam.setPosition(0.0, 0.0, 1.0);
	testcam.setUp(0.0, 1.0, 0.0);
	testcam.setForward(0.0, 0.0, 0.0);
	testcam.setLeft(1.0, 0.0, 0.0);

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
		drawHandle(hDC, scenes, texMap, &camera, &position);
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
	glm::vec3 newPosition;
	glm::vec4 trans;
	glm::vec3 rotated;
	glm::vec3 newForward;
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
			newPosition = camera.getPosition() - camera.getForward();
			glm::normalize(&newPosition);
			camera.setPosition(camera.getPosition().x - (velocity*newPosition.x),
					camera.getPosition().y - (velocity*newPosition.y),
					camera.getPosition().z - (velocity*newPosition.z));
			break;
		case VK_DOWN://move away from lookat
			newPosition = camera.getPosition() - camera.getForward();
			glm::normalize(&newPosition);
			camera.setPosition(camera.getPosition().x + (velocity*newPosition.x),
					camera.getPosition().y + (velocity*newPosition.y),
					camera.getPosition().z + (velocity*newPosition.z));
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
			//camera.print();
			//camera.anglesToAxes(lookUp);
			//rotated = glm::vec3(glm::rotate(camera.getForward(), 1.0f, camera.getLeft()));
			//camera.setForward((glm::mat3)glm::translate(-camera.getPosition())*camera.getForward());
			//camera.setLeft((glm::mat3)glm::translate(-camera.getPosition())*camera.getLeft());
			//camera.print();
			//camera.setForward(glm::rotate(camera.getForward(), 1.0f, camera.getLeft()));
			//camera.setForward((glm::mat3)glm::translate(camera.getPosition())*camera.getForward());
			//camera.setForward(glm::mat3(glm::rotate(0.5f, camera.getLeft()))*camera.getForward());
			//camera.setLeft((glm::mat3)glm::translate(camera.getPosition())*camera.getLeft());

			trans = -glm::translate(camera.getPosition())*glm::vec4(camera.getForward(), 1);
			camera.setForward(glm::vec3(trans));
			cout<<"current look at is x:"<<camera.getForward().x
			<<" y:"<<camera.getForward().y <<" z:" << camera.getForward().z<<endl;
			newForward = glm::mat3(glm::rotate(0.5f, camera.getLeft()))*camera.getForward();
			camera.setForward(newForward);
			cout<<"look at is now x:"<<camera.getForward().x
			<<" y:"<<camera.getForward().y <<" z:" << camera.getForward().z<<endl;
			trans = -glm::translate(camera.getPosition())*glm::vec4(camera.getForward(), 1);
			camera.setForward(glm::vec3(trans));
			camera.print();

			break;
		case VK_NUMPAD5:
			cout<<"current look at is x:"<<camera.getForward().x
			<<" y:"<<camera.getForward().y <<" z:" << camera.getForward().z<<endl;
			camera.anglesToAxes(lookUp);
			cout<<"look at is now x:"<<camera.getForward().x
					<<" y:"<<camera.getForward().y <<" z:" << camera.getForward().z<<endl;
			break;
		case VK_NUMPAD4:
			//camera.anglesToAxes(lookLeft);
			lookUp.x = camera.getForward().x + velocity;
			lookUp.y = camera.getForward().y;
			lookUp.z = camera.getForward().z;
			glm::normalize(&lookUp);
			//camera.lookAtToAxes(lookUp);
			break;
		case VK_NUMPAD6:
			//camera.anglesToAxes(lookRight);
			lookUp.x = camera.getForward().x - velocity;
			lookUp.y = camera.getForward().y;
			lookUp.z = camera.getForward().z;
			glm::normalize(&lookUp);
			//camera.lookAtToAxes(lookUp);
			break;
		case VK_SPACE:
			cout<<"current look at is x:"<<testcam.getForward().x
			<<" y:"<<testcam.getForward().y <<" z:" << testcam.getForward().z<<endl;
			trans = -glm::translate(testcam.getPosition())*glm::vec4(testcam.getForward(), 1);
			testcam.setForward(glm::vec3(trans));
			cout<<"look at is now x:"<<testcam.getForward().x
			<<" y:"<<testcam.getForward().y <<" z:" << testcam.getForward().z<<endl;
			testcam.print();
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
