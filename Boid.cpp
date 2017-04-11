/*
 * Boid.cpp
 *
 *  Created on: Apr 11, 2017
 *      Author: dannyphantom
 */

#include "Boid.h"
#include "Sphere.h"
#include <iostream>
#include <math.h>
#include "SceneParameters.h"

Boid::Boid() {
	currentNormal = glm::vec3(0, 1, 0);

}

Boid::~Boid() {
	// TODO Auto-generated destructor stub
}

std::vector<Boid::BoidInfo> Boid::calculateDistanceToBoids(std::vector<Boid *> boids) {
	std::vector<BoidInfo> boidsInfo;
	for (Boid *b : boids) {
		glm::vec3 vec = position - b->getPosition();
		float distSquared = glm::dot(vec, vec);
		bool isVisible = glm::dot(velocity, -vec) > std::cos(SceneParameters::fovRadians);
		boidsInfo.push_back(BoidInfo(b, distSquared, isVisible));
	}
	return boidsInfo;
}

std::vector<Boid::BoidInfo> Boid::getVisibleBoidsInRadius(std::vector<BoidInfo> boids, float radius) {
	float radiusSquared = radius * radius;
	std::vector<BoidInfo> boidsInRadius;
	for (BoidInfo b : boids) {
		if (b.isVisible && b.distanceToBoid < radiusSquared && b.boid != this) {
			boidsInRadius.push_back(b);
		}
	}
	return boidsInRadius;
}

glm::vec3 Boid::calculateAvoidance(std::vector<BoidInfo> boidsInfo) {
	int totalNum = 0;
	glm::vec3 result = glm::vec3(0.0f);
	for (BoidInfo b : getVisibleBoidsInRadius(boidsInfo, SceneParameters::avoidRadius)) {
		glm::vec3 vecFromBoid = position - b.boid->getPosition();
		float weight = b.distanceToBoid / SceneParameters::avoidRadiusSQ;
		if (weight == 0) {
			weight = 0.00001f;
		}
		weight = 1 / (pow(weight, 2)) - 1;
		result += weight * glm::normalize(vecFromBoid);
		totalNum++;
	}
	if (totalNum == 0) { totalNum = 1; }
	return result / (float)(totalNum);
}

glm::vec3 Boid::calculateFollow(std::vector<BoidInfo> boidsInfo) {
	int totalNum = 0;
	glm::vec3 result = glm::vec3(0.0f);
	for (BoidInfo b : getVisibleBoidsInRadius(boidsInfo, SceneParameters::followRadius)) {
		glm::vec3 vecToBoid = b.boid->getPosition() - position;
		float weight = b.distanceToBoid / SceneParameters::followRadiusSQ;
		if (weight == 0) {
			weight = 0.00001f;
		}
		result += (float)(1 / (pow(weight, 1.4)) - 1) * glm::normalize(vecToBoid);
		totalNum++;
	}
	if (totalNum == 0) { totalNum = 1; }
	return result / (float)(totalNum);
}

glm::vec3 Boid::calculateMatchVelocity(std::vector<BoidInfo> boidsInfo) {
	int totalNum = 0;
	glm::vec3 result = glm::vec3(0.0f);
	for (BoidInfo b : getVisibleBoidsInRadius(boidsInfo, SceneParameters::speedMatchRadius)) {
		float weight = b.distanceToBoid / SceneParameters::speedMatchRadiusSQ;
		if (weight == 0) {
			weight = 0.00001f;
		}
		result += (float)(1/( pow(weight, 1.2) ) - 1) * b.boid->getVelocity();
		totalNum++;
	}
	if (totalNum == 0) { totalNum = 1; }
	return result / (float)(totalNum);
}


void Boid::calculateModelMatrix(float dt) {
	glm::vec3 velocityNorm = glm::normalize(velocity);
	glm::vec3 normal = aimingVelocity - glm::dot(aimingVelocity, velocityNorm) * velocityNorm;
	if (glm::length(normal) < 0.01f) {
		normal = glm::vec3(0, 1, 0);
	} else {
		normal = glm::normalize(normal);
	}
	currentNormal = glm::normalize(currentNormal + normal * (float)pow(dt, 5));

	glm::vec3 tangent = velocityNorm;
	glm::vec3 binormal = glm::cross(tangent, currentNormal);
	glm::mat4 modelMatrix = glm::mat4(
				glm::vec4(binormal, 0),
				glm::vec4(currentNormal, 0),
				glm::vec4(tangent, 0),
				glm::vec4(position, 1));
	setModelMatrix(modelMatrix);

}

glm::vec3 Boid::calculateObstacleAvoidance(std::vector<Obstacle *> obstacles) {
	glm::vec3 result(0);
	int totalNum = 0;
	for (Obstacle *o : obstacles) {
		glm::vec3 avoidVec = o->getAvoidVector(position, velocity);
		if (avoidVec.x != 0 || avoidVec.y != 0 || avoidVec.z != 0) {
			result += avoidVec;
			totalNum++;
		}
	}
	if (totalNum == 0) { totalNum = 1; }
	return result / (float)totalNum;
}

void Boid::update(std::vector<Boid*> boids, std::vector<Obstacle *> obstacles, float dt) {
	std::vector<BoidInfo> boidsInfo = calculateDistanceToBoids(boids);
	glm::vec3 accel = SceneParameters::AvoidCoef * calculateAvoidance(boidsInfo) +
			SceneParameters::speedMatchCoef * calculateMatchVelocity(boidsInfo) +
			SceneParameters::followCoef * calculateFollow(boidsInfo) +
			SceneParameters::obstacleAvoidCoef * calculateObstacleAvoidance(obstacles);

	aimingVelocity = velocity + (accel - glm::vec3(0, 9.8, 0)) * dt;
	calculateModelMatrix(dt);

	velocity += accel * dt;
	if (glm::length(velocity) > 45) { velocity = glm::normalize(velocity) * 45.0f;}
	if (glm::length(velocity) < 15) { velocity = glm::normalize(velocity) * 15.0f;}
	position += velocity * dt;
	if (glm::length(position) > SceneParameters::worldRadius) {
		position = glm::normalize(position) * SceneParameters::worldRadius;
		//direct them towards the center
		velocity = -glm::normalize(position);
	}
}
