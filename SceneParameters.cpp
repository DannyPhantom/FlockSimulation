#include "SceneParameters.h"
#include "Libraries/freeglut/freeglut.h"

int SceneParameters::screenHeight;
int SceneParameters::screenWidth;
bool SceneParameters::isFullScreen;
float SceneParameters::zNear;
float SceneParameters::zFar;

float SceneParameters::obstacleAvoidCoef = 30.0f;
float SceneParameters::AvoidCoef = 5.7f;
float SceneParameters::speedMatchCoef = 0.7f;
float SceneParameters::followCoef = 0.7f;
float SceneParameters::fovRadians = 1.7708;
float SceneParameters::obstacleAvoidRadius = 2;
float SceneParameters::obstacleAvoidRadiusSQ = 4;
float SceneParameters::avoidRadius = 4;
float SceneParameters::avoidRadiusSQ = 16;
float SceneParameters::speedMatchRadius = 5;
float SceneParameters::speedMatchRadiusSQ = 25;
float SceneParameters::followRadius = 10;
float SceneParameters::followRadiusSQ = 100;
float SceneParameters::worldRadius = 30;
int SceneParameters::numOfBoids = 900;
float SceneParameters::boidsGridSize = 30;

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
