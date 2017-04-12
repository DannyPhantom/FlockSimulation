#include "Scene.h"
#include "ShaderLoader.h"
#include "ObjLoader.h"
#include "Boid.h"
#include "Sphere.h"
#include "SceneParameters.h"
#include "Libraries/glm/gtc/matrix_transform.hpp"
#include <chrono>
#include "Randomizer.h"

Scene::Scene()
{
}

Scene::~Scene()
{
}

void Scene::initializeScene() {
	//define the projection matrix (it's constant and never changes)
	projectionMatrix = glm::perspective(
		glm::radians(90.0f),
		1.0f * SceneParameters::getScreenWidth() / SceneParameters::getScreenHeight(),
		SceneParameters::getZNear(),
		SceneParameters::getZFar()
	);

	//define the inverse of the projection matrix
	inverseProjectionMatrix = glm::inverse(projectionMatrix);

	//load all the stuff
	loadShaders();
	loadObjects();
	loadOtherStuff();
	placeObjects();
}

void Scene::renderPhong() {
	std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glUseProgram(basicPhongShader);

	glUniformMatrix4fv(glGetUniformLocation(basicPhongShader, "ProjectionMatrix"), 1, false, &(getProjectionMatrix()[0][0]));

	for (SceneObject *obj : objects) {
		obj->draw(basicPhongShader, cam.getViewMatrix());
	}
}

void Scene::renderScene(float dt) {
	//update the camera's position
	cam.update(dt);

	for (Boid *b : boids) {
		glm::mat4 proj = getProjectionMatrix();
		glm::mat4 view = cam.getViewMatrix();

		//code from http://antongerdelan.net/opengl/raycasting.html
		float x = (2.0f * currentMousePos.x) - 1.0f;
		float y = (2.0f * currentMousePos.y) - 1.0f;
		float z = 1.0f;
		glm::vec3 ray_nds = glm::vec3(x, y, z);
		glm::vec4 ray_clip = glm::vec4(ray_nds.x, ray_nds.y, -1.0, 1.0);
		glm::vec4 ray_eye = inverse(proj) * ray_clip;
		ray_eye = glm::vec4(ray_eye.x, ray_eye.y, -1.0, 0.0);
		glm::vec3 ray_wor = glm::vec3(inverse(view) * ray_eye);
		// don't forget to normalise the vector at some point
		ray_wor = glm::normalize(ray_wor);

		b->update(boids, obstacles, dt, cam.getPosition(), glm::normalize(ray_wor), mouseAttractionEnabled);

	}

	renderPhong();
}

void Scene::loadShaders() {
	ShaderLoader loader;
	basicPhongShader = loader.loadShader("Shaders/PhongVertexShader.glsl", "Shaders/PhongFragmentShader.glsl");
}

void Scene::loadOtherStuff() {
	
}

void Scene::loadObjects() {
	ObjLoader loader;
	ship = loader.loadFromFile("Models/WraithRaiderStarship/Wraith Raider Starship.obj");
	sphere = loader.loadFromFile("Models/Sphere.obj");
	SceneObject *skybox = loader.loadFromFile("Models/Skybox.obj");
	skybox -> setScale (glm::vec3(110, 110, 110));
	objects.push_back(skybox);
}

void Scene::placeObjects() {
	int numOfBoidsPerAxis = std::cbrt(SceneParameters::numOfBoids);
	glm::vec3 distanceBetweenBoids = glm::vec3(SceneParameters::boidsGridSize) / (float)(numOfBoidsPerAxis + 1);

	int start = -numOfBoidsPerAxis / 2;
	int end = numOfBoidsPerAxis / 2;
	for (int i = start; i < end; i++) {
		for (int j = start; j < end; j++) {
			for (int k = start; k < end; k++) {
				Boid *b = new Boid();
				b->setMeshes(*ship->getMeshes());
				b->setPosition(glm::vec3(i * distanceBetweenBoids.x, j * distanceBetweenBoids.y, k * distanceBetweenBoids.z));
				glm::vec3 velocity = glm::vec3(Randomizer::getRandomFloat(-25.0f, 25.0f), Randomizer::getRandomFloat(-25.0f, 25.0f), Randomizer::getRandomFloat(-25.0f, 25.0f));
				b->setVelocity(velocity);
				objects.push_back(b);
				boids.push_back(b);
			}
		}
	}

	Sphere *world = new Sphere(SceneParameters::worldRadius);
	world->setMeshes(*sphere->getMeshes());
	world->setIsVisible(false);
	obstacles.push_back(world);
	objects.push_back(world);

	start = - SceneParameters::boidsGridSize;
	end = SceneParameters::boidsGridSize;
	for (int i = start; i < end; i++) {
		for (int j = start; j < end; j++) {
			for (int k = start; k < end; k++) {
				if (Randomizer::getRandomFloat(0.0f, 1.0f) < 0.0003f) {
					Sphere *s = new Sphere(Randomizer::getRandomFloat(0.1f, 2.0f));
					s->setMeshes(*sphere->getMeshes());
					s->setPosition(glm::vec3(i, j, k));
					objects.push_back(s);
					obstacles.push_back(s);
				}
			}
		}
	}

}

glm::mat4 Scene::getProjectionMatrix() {
	return projectionMatrix;
}

glm::mat4 Scene::getInverseProjectionMatrix() {
	return inverseProjectionMatrix;
}
