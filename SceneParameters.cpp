#include "SceneParameters.h"
#include "Libraries/freeglut/freeglut.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>

int SceneParameters::screenHeight;
int SceneParameters::screenWidth;
bool SceneParameters::isFullScreen;
float SceneParameters::zNear;
float SceneParameters::zFar;

float SceneParameters::obstacleAvoidCoef;
float SceneParameters::AvoidCoef;
float SceneParameters::speedMatchCoef;
float SceneParameters::followCoef;
float SceneParameters::fovRadians;
float SceneParameters::obstacleAvoidRadius;
float SceneParameters::obstacleAvoidRadiusSQ;
float SceneParameters::avoidRadius;
float SceneParameters::avoidRadiusSQ;
float SceneParameters::speedMatchRadius;
float SceneParameters::speedMatchRadiusSQ;
float SceneParameters::followRadius;
float SceneParameters::followRadiusSQ;
float SceneParameters::worldRadius;
int SceneParameters::numOfBoids;
float SceneParameters::boidsGridSize;
float SceneParameters::mouseCoef;
float SceneParameters::mouseRadius;
float SceneParameters::mouseRadiusSQ;

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

	loadFile();
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

float SceneParameters::loadFile() {
	std::ifstream infile("params.txt");
	std::string line;
	std::vector<float> values;
	while (std::getline(infile, line))
	{
	    std::istringstream iss(line);
	    float val;
	    if (!(iss >> val)) { std::cout << "Error when loading the file" << std::endl; break; } // error
	    values.push_back(val);
	}

	obstacleAvoidCoef = values[0];
	AvoidCoef = values[1];
	speedMatchCoef = values[2];
	followCoef = values[3];
	fovRadians = values[4];
	obstacleAvoidRadius = values[5];
	obstacleAvoidRadiusSQ = obstacleAvoidRadius * obstacleAvoidRadius;
	avoidRadius = values[6];
	avoidRadiusSQ = avoidRadius * avoidRadius;
	speedMatchRadius = values[7];
	speedMatchRadiusSQ = speedMatchRadius * speedMatchRadius;
	followRadius = values[8];
	followRadiusSQ = followRadius * followRadius;
	worldRadius = values[9];
	numOfBoids = values[10];
	boidsGridSize = values[11];
	mouseRadius = values[12];
	mouseRadiusSQ = mouseRadius * mouseRadius;
	mouseCoef = values[13];
}
