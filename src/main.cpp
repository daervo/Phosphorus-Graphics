#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>
#include "../headers/camera.h"
#include "../headers/Textures.h"
#include "../headers/DrawHandler.h"
#include <hid.hpp>
static void error_callback(int , const char* description)
{
    fputs(description, stderr);
}
/*static void key_callback(GLFWwindow* window, int key, int , int action, int )
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}*/
int main(void)
{
    GLFWwindow* window;
    glfwSetErrorCallback(error_callback);
    if (!glfwInit())
        exit(EXIT_FAILURE);
    window = glfwCreateWindow(640, 480, "Simple example", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(window);
    //glfwSetKeyCallback(window, key_callback);

    /*Graphics things*/
    DrawHandler hDraw(window);
    MeshLoader mesh1 = MeshLoader("C:\\Users\\Ervin\\workspace2\\phosphorus\\src\\graphics\\Zaralok.obj",
    		"C:\\Users\\Ervin\\workspace2\\phosphorus\\src\\graphics\\");
    CustomMesh customMesh = CustomMesh(
    				new glm::vec3(-1.0, 0.0, -1.0),
    				new glm::vec3(-1.0, 0.0, 1.0),
    				new glm::vec3(1.0, 0.0, 1.0),
    				new glm::vec3(1.0, 0.0, -1.0),
    				"C:\\Users\\Ervin\\workspace2\\phosphorus\\src\\graphics\\Textures\\9325284-green-grass-texture.tga"
    				);
    Camera camera1 = Camera();
    Camera camera2 = Camera();
	camera1.setPosition(0.0, 0.0, 1.0);
	camera1.setLookAt(0.0, 0.0, 0.0);
	camera2.setPosition(0.0, 2.0, 1.0);
	camera2.setLookAt(0.0, 0.0, 0.0);
	mesh1.setTranslation(0, 0, -1);
	mesh1.setScale(0.01f);
	mesh1.setRotations(0.0, 33.0, 0.0f);
    hDraw.addMeshLoader(&mesh1);
	hDraw.addCamera(&camera1);
	hDraw.addCamera(&camera2);
	hDraw.addCustomMesh(&customMesh);

	auto hid = phosphorus::human_interface_device(window, GLFW_STICKY_KEYS, GL_TRUE);

	hid.poll();
	std::pair<double, double> current = hid.get_cursor_position();
	std::pair<double, double> previous = hid.get_cursor_position();
    while (!glfwWindowShouldClose(window))
    {

    	hid.poll();
    	current = hid.get_cursor_position();
    	hid.on_mouse_down(phosphorus::mouse_button::left,
    			[&]{hDraw.getCurrentCamera()->turn ((current.first - previous.first), (current.second - previous.second), 0.005);});
    	hid.on_key_down('W', [&]{hDraw.getCurrentCamera()->moveForward(0.05);});
    	hid.on_key_down('S', [&]{hDraw.getCurrentCamera()->moveForward(-0.05);});
    	hid.on_key_down('A', [&]{hDraw.getCurrentCamera()->moveRight(-0.05);});
    	hid.on_key_down('D', [&]{hDraw.getCurrentCamera()->moveRight(0.05);});

    	hid.on_key_down('1', [&]{hDraw.setCurrentCamera(1);});
    	hid.on_key_down('2', [&]{hDraw.setCurrentCamera(1);});

    	hDraw.draw();

    	previous = current;
    }
    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}
