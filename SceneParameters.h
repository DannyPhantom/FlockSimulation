#pragma once

/*
	Parameters for the scene
*/
class SceneParameters
{
public:
	/*
	Initializes the parameters
	*/
	static void initialize();
	
	/*
		Returns the screen height
	*/
	static int getScreenHeight();

	/*
		Returns the screen width
	*/
	static int getScreenWidth();

	/*
		Returns the near clipping plane
	*/
	static float getZNear();

	/*
		Returns the far clipping plane
	*/
	static float getZFar();


	static float obstacleAvoidCoef;
	static float AvoidCoef;
	static float speedMatchCoef;
	static float followCoef;
	static float fovRadians; //90 degrees
	static float obstacleAvoidRadius;
	static float obstacleAvoidRadiusSQ;
	static float avoidRadius;
	static float avoidRadiusSQ;
	static float speedMatchRadius;
	static float speedMatchRadiusSQ;
	static float followRadius;
	static float followRadiusSQ;
	static float worldRadius;
	static int numOfBoids;
	static float boidsGridSize;

private:
	/*
		No contructor, since all methods are static
	*/
	SceneParameters();
	~SceneParameters();

	static float loadFile();

private:
	static int screenHeight;
	static int screenWidth;
	static bool isFullScreen;
	static float zNear;
	static float zFar;
};

