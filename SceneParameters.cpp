#include "SceneParameters.h"
#include "Libraries/freeglut/freeglut.h"

int SceneParameters::screenHeight;
int SceneParameters::screenWidth;
bool SceneParameters::isFullScreen;
float SceneParameters::zNear;
float SceneParameters::zFar;

float SceneParameters::obstacleAvoidCoef = 10005.0f;
float SceneParameters::AvoidCoef = 17.7f;
float SceneParameters::speedMatchCoef = 1.0f;
float SceneParameters::followCoef = 1.0f;
float SceneParameters::fovRadians = 1.7708;
float SceneParameters::obstacleAvoidRadius = 5;
float SceneParameters::obstacleAvoidRadiusSQ = 25;
float SceneParameters::avoidRadius = 3;
float SceneParameters::avoidRadiusSQ = 9;
float SceneParameters::speedMatchRadius = 15;
float SceneParameters::speedMatchRadiusSQ = 225;
float SceneParameters::followRadius = 15;
float SceneParameters::followRadiusSQ = 225;
float SceneParameters::worldRadius = 30;
int SceneParameters::numOfBoids = 700;
float SceneParameters::boidsGridSize = 20;

SceneParameters::SceneParameters()
{
}


SceneParameters::~SceneParameters()
{
}

void SceneParameters::initialize() {
	zNear = 0.01f;
	zFar = 50000.0f;
	screenHeight = 900;
	screenWidth = 1500;
	isFullScreen = false;





	if (isFullScreen) {
		screenWidth = glutGet(GLUT_WINDOW_WIDTH);
		screenHeight = glutGet(GLUT_WINDOW_HEIGHT);
	}
}

int SceneParameters::getScreenHeight() {
	return screenHeight;
}

int SceneParameters::getScreenWidth() {
	return screenWidth;
}

float SceneParameters::getZNear() {
	return zNear;
}

float SceneParameters::getZFar() {
	return zFar;
}
