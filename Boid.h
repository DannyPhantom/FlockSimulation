/*
 * Boid.h
 *
 *  Created on: Apr 11, 2017
 *      Author: dannyphantom
 */

#ifndef BOID_H_
#define BOID_H_

#include "SceneObject.h"
class Obstacle;

class Boid : public SceneObject {
private:
	struct BoidInfo {
		Boid *boid;
		float distanceToBoid;
		bool isVisible;

		BoidInfo(Boid *b, float distanceToBoid, bool isVisible) : boid(b), distanceToBoid(distanceToBoid), isVisible(isVisible) {

		}
	};

	void calculateModelMatrix(float dt);
	std::vector<BoidInfo> calculateDistanceToBoids(std::vector<Boid *> boids);
	std::vector<BoidInfo> getVisibleBoidsInRadius(std::vector<BoidInfo> boids, float radius);
	glm::vec3 calculateAvoidance(std::vector<BoidInfo> boidsInfo);
	glm::vec3 calculateMatchVelocity(std::vector<BoidInfo> boidsInfo);
	glm::vec3 calculateFollow(std::vector<BoidInfo> boidsInfo);
	glm::vec3 calculateObstacleAvoidance(std::vector<Obstacle *> obstacles);
	glm::vec3 calculateMouseAttraction(glm::vec3 origin, glm::vec3 dir);

	void setModelMatrix(glm::mat4 mm) {modelMatrix = mm;}

	glm::vec3 velocity, aimingVelocity;
	glm::vec3 currentNormal;
public:
	Boid();
	virtual ~Boid();

	void update(std::vector<Boid*> boids, std::vector<Obstacle *> obstacles, float dt, glm::vec3 camPos, glm::vec3 mouseRay, bool useMouse);
	void setVelocity(glm::vec3 vel) {velocity = vel; aimingVelocity = vel;}
	glm::vec3 getPosition() {return position;}
	glm::vec3 getVelocity() { return velocity; }
};

#endif /* BOID_H_ */
