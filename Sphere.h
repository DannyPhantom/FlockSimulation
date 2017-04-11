/*
 * Sphere.h
 *
 *  Created on: Apr 11, 2017
 *      Author: dannyphantom
 */

#ifndef SPHERE_H_
#define SPHERE_H_

#include "Obstacle.h"

class Sphere: public Obstacle {
private:
	float radius;
public:
	Sphere(float radius);
	virtual ~Sphere();

	void create();
	glm::vec3 getAvoidVector(glm::vec3 from, glm::vec3 dir);
};

#endif /* SPHERE_H_ */
