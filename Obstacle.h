/*
 * Obstacle.h
 *
 *  Created on: Apr 11, 2017
 *      Author: dannyphantom
 */

#ifndef OBSTACLE_H_
#define OBSTACLE_H_

#include "SceneObject.h"

class Obstacle: public SceneObject {
public:
	Obstacle();
	virtual ~Obstacle();

	virtual void create() = 0;
	virtual glm::vec3 getAvoidVector(glm::vec3 from, glm::vec3 dir) = 0;
};

#endif /* OBSTACLE_H_ */
