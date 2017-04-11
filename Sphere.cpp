/*
 * Sphere.cpp
 *
 *  Created on: Apr 11, 2017
 *      Author: dannyphantom
 */

#include "Sphere.h"
#include "SceneParameters.h"
#include <iostream>
#include <math.h>

#define TWO_PI 6.28318530718

Sphere::Sphere(float radius) : radius(radius) {
	setScale(glm::vec3(radius * 2, radius * 2, radius * 2));
}

Sphere::~Sphere() {
}


void Sphere::create() {

}

glm::vec3 Sphere::getAvoidVector(glm::vec3 from, glm::vec3 dir) {
	glm::vec3 avoidVec(0);
	glm::vec3 closestPoint = radius * glm::normalize(from - position);
	glm::vec3 vecToClosestPoint = closestPoint - from;
	if (glm::dot(vecToClosestPoint, vecToClosestPoint) < SceneParameters::obstacleAvoidRadiusSQ && glm::dot(vecToClosestPoint, dir) > std::cos(SceneParameters::fovRadians)) {
		float weight = glm::dot(vecToClosestPoint, vecToClosestPoint) / SceneParameters::obstacleAvoidRadiusSQ;
		if (weight == 0) {
			weight = 0.00001f;
		}
		weight = 1 / (weight * weight) - 1;
		avoidVec = weight * -vecToClosestPoint;
	} else {
		avoidVec = glm::vec3(0, 0, 0);
	}

	return avoidVec;
}
