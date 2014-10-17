#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>
#include "../headers/camera.h"
#include "../headers/Textures.h"
#include "../headers/DrawHandler.h"
#include <hid.hpp>
#include <physics/physics.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <networks/GameState.h>
#include <networks/GameClient.h>
#include <networks/GamePacket.h>

using namespace phosphorus;

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
    MeshLoader otherPlayer = MeshLoader("C:\\Users\\Ervin\\workspace2\\Phosphorus-Graphics\\Zaralok.obj",
    		"C:\\Users\\Ervin\\workspace2\\Phosphorus-Graphics\\");
    MeshLoader bullet = MeshLoader("C:\\Users\\Ervin\\workspace2\\Phosphorus-Graphics\\test.3ds");
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
	camera2.setPosition(5.0, 0.0, 0.0);
	camera2.setLookAt(4.0, 0.0, 0.0);
	//mesh1.setTranslation(0, 0, -1);
	otherPlayer.setScale(0.01f);
	//mesh1.setRotations(0.0, 33.0, 0.0f);
    hDraw.addMeshLoader(&otherPlayer);
	hDraw.addCamera(&camera1);
	hDraw.addCamera(&camera2);
	hDraw.addCustomMesh(&customMesh);
	hDraw.addMeshLoader(&bullet);
	bullet.setScale(0.1);
	phosphorus::physics::PhysicalObject otherPlayer_phys = phosphorus::physics::PhysicalObject(glm::vec3(0, 0, 0),
			glm::vec3(0, 0, 0),
			false,
			1.0
			);

	auto hid = phosphorus::human_interface_device(window, GLFW_STICKY_KEYS, GL_TRUE);

	hid.poll();
	std::pair<double, double> current = hid.get_cursor_position();
	std::pair<double, double> previous = hid.get_cursor_position();
	glm::vec3 shootAt;
	phosphorus::physics::PhysicalObject bullet_phys = phosphorus::physics::PhysicalObject(glm::vec3(0, 0, 0),
			glm::vec3(0, 0, 0),
			false,
			1.0
			);
	bullet.setTranslation(10, 10, 10);
	bullet_phys.set_position(glm::vec3(10, 10, 10));

	//Player stats
	float hp = 100;

	//Server vars
	GameClient gc = GameClient();
	GamePacket gp = GamePacket();
	GameState gs = GameState(0);
	char packet[36];
	char reply [76];

    while (!glfwWindowShouldClose(window))
    {
    	//Set HID controls
    	hid.poll();
    	current = hid.get_cursor_position();
    	hid.on_mouse_down(phosphorus::mouse_button::left,
    			[&]{hDraw.getCurrentCamera()->turn ((current.first - previous.first), (current.second - previous.second), 0.005);});
    	hid.on_key_down('W', [&]{hDraw.getCurrentCamera()->moveForward(0.05);});
    	hid.on_key_down('S', [&]{hDraw.getCurrentCamera()->moveForward(-0.05);});
    	hid.on_key_down('A', [&]{hDraw.getCurrentCamera()->moveRight(-0.05);});
    	hid.on_key_down('D', [&]{hDraw.getCurrentCamera()->moveRight(0.05);});
    	hid.on_key_down(GLFW_KEY_LEFT_SHIFT, [&]{
    		//set phys object to camera location
    		bullet_phys.set_position(camera2.getPosition());
        	bullet.setTranslation(bullet_phys.position().x, bullet_phys.position().y, bullet_phys.position().z);
        	shootAt = -100.0f * glm::normalize(camera2.getPosition() - camera2.getLookAt());

        	bullet_phys.apply_force(&shootAt);
    	});

    	hid.on_key_down('1', [&]{hDraw.setCurrentCamera(0);});
    	hid.on_key_down('2', [&]{hDraw.setCurrentCamera(1);});

    	//update position of bullet
    	bullet_phys.update_position(0.01);
    	bullet.setTranslation(bullet_phys.position().x, bullet_phys.position().y, bullet_phys.position().z);

    	//Draw
    	hDraw.draw();

    	//Check for collision
    	if (phosphorus::physics::GJK_collision(bullet.getVertices(), otherPlayer.getVertices())){
    		cout<<"hit!!"<<endl;
    	}

    	//Send To Server
    	gc.startConnection(8085, "localhost");
    	gp.createUpdatePacket(packet, 0, camera2.getPosition(), camera2.getLookAt(), hp);
    	gc.sendToServer(packet, reply);
    	gs.updateState(reply);
    	gc.close();

    	//Update client state
    	otherPlayer.setTranslation(gs.get(gs.PLAYER_0_POSITION, 1),
    			gs.get(gs.PLAYER_0_POSITION+4, 1),
    			gs.get(gs.PLAYER_0_POSITION+8, 1)
    			);


    	previous = current;
    }
    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}
