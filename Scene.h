#pragma once

#include <vector>
#include "SceneObject.h"
#include "Camera.h"
#include <chrono>
#include <string>

class Boid;
class Sphere;
class Obstacle;

/*
	The main class of the program.
	Contains all the UI's, objects, basic controls, etc.
*/
class Scene
{
public:
	Scene();
	~Scene();

	/*
		Initializes the scene
	*/
	void initializeScene();

	/*
		Renders the scene
	*/
	void renderScene(float dt);

	/*
		Returns the scene's camera (controlled by the user)
	*/
	Camera *getCamera() { return &cam; }

	void enableMouseAttraction() { mouseAttractionEnabled = true; }
	void disableMouseAttraction() { mouseAttractionEnabled = false; }
	void setCurrentMousePos(glm::vec2 pos) {
		currentMousePos = pos;
		currentMousePos.y = 1 - currentMousePos.y;
		//currentMousePos = currentMousePos * 2.0f - 1.0f;
	}

private:

	/*
		Loads all the shaders
	*/
	void loadShaders();
	
	/*
		Loads all the objects
	*/
	void loadObjects();

	/*
		Loads some various stuff such as
		ssao kernel, ssao noise texture,
		etc.
	*/
	void loadOtherStuff();
	
	/*
		Places all the objects in the scene, i.e.
		assigns the position and scales for the skybox and
		the city
	*/
	void placeObjects();

	/*
		Returns the projection matrix for the scene
	*/
	glm::mat4 getProjectionMatrix();

	/*
		Returns the inverse projection matrix for the scene
	*/
	glm::mat4 getInverseProjectionMatrix();

	/*
		Renders the scene using phong shading
	*/
	void renderPhong();

private:
	std::vector<SceneObject *> objects;
	std::vector<Boid *> boids;
	std::vector<Obstacle *> obstacles;

	glm::mat4 projectionMatrix;
	glm::mat4 inverseProjectionMatrix;

	//shaders
	GLuint basicPhongShader;
	Camera cam;

	SceneObject *ship, *sphere;

	glm::vec2 currentMousePos;
	bool mouseAttractionEnabled;
};

