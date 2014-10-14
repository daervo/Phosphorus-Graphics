/*
 * DrawHandler.h
 *
 *  Created on: 11 Oct 2014
 *      Author: Ervin
 */

#ifndef DRAWHANDLER_H_
#define DRAWHANDLER_H_
#include"../headers/camera.h"
#include"../headers/meshLoader.h"
#include"../headers/CustomMesh.h"

class DrawHandler {
	std::vector<MeshLoader*> meshLoaders;
	std::vector<CustomMesh*> customMeshes;
	std::map<std::string, GLuint*> textureIdMap;
	std::vector<Camera*> cameras;
	GLFWwindow* window;
	bool lightingEnabled = true;
	int currentCam = 0;
	int perspectiveMode;
	float frustrum[6] = {-0.5, 0.5, -0.5, 0.5, 5, 100};
	float ortho[6] = {-0.5, 0.5, -0.5, 0.5, -0.25, 20};
	float perspectiveValues[6];
	bool guideEnabled = false;
	int const NUM_PERSPECTIVE_VALUES = 6;


private:
	void setUpLighting();
	void setUpPerspective();

public:
	/**
	 * Use Frustum calculations for the perspective.
	 */
	int const PH_FRUSTRUM = 0;
	/**
	 * Use Ortho calculations for perspective.
	 */
	int const PH_ORTHO = 1;

	/**
	 * Constructor
	 * @param nWindow GLFW window
	 */
	DrawHandler(GLFWwindow* nWindow);
	virtual ~DrawHandler();
	/**
	 * Draw the objects
	 */
	void draw();
	/**
	 * Add a new Camera object
	 * @param camera Camera object
	 */
	void addCamera(Camera* camera){
		cameras.push_back(camera);
	}
	/**
	 * Get the camera at num
	 * @param num the camera to return
	 * @return Camera*
	 */
	Camera* getCamera(int num){
		return cameras[num];
	}
	/**
	 * Adds a meshloader to the list
	 * @param meshLoader adds this meshLoader
	 */
	void addMeshLoader(MeshLoader* meshLoader){
		meshLoaders.push_back(meshLoader);
	}
	/**
	 * Enables/disables lighting. Lighting is enabled by default
	 * @param enabled defaulted to true
	 */
	void enableLighting(boolean enabled = true){
		lightingEnabled = enabled;
	}
	/**
	 * Set the current camera.
	 * @param cameraNum current camera number
	 */
	void setCurrentCamera(int cameraNum){
		currentCam = cameraNum;
	}
	/**
	 * Gets current camera
	 * @return current camera
	 */
	Camera* getCurrentCamera(){
		return cameras[currentCam];
	}
	/**
	 * Enables/disables a guide plane
	 * @param enabled defaulted to true
	 */
	void enableGuide(bool enabled = true){
		guideEnabled = enabled;
	}
	/**
	 * Sets perspective mode
	 * @param mode use PH_ORTHO or PH_FRUSTRUM
	 */
	void setPerspectiveMode (int mode);
	/**
	 * Sets the values for the perspective mode
	 * @param v1 look up glFrustrum/glOrtho for meanings
	 * @param v2 look up glFrustrum/glOrtho for meanings
	 * @param v3 look up glFrustrum/glOrtho for meanings
	 * @param v4 look up glFrustrum/glOrtho for meanings
	 * @param v5 look up glFrustrum/glOrtho for meanings
	 * @param v6 look up glFrustrum/glOrtho for meanings
	 */
	void setPerspectiveValues(float v1, float v2, float v3, float v4, float v5, float v6);
	void addCustomMesh(CustomMesh* customMesh);
};

#endif /* DRAWHANDLER_H_ */
