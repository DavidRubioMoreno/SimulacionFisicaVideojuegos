#pragma once

#include <PxPhysicsAPI.h>
#include "RenderUtils.hpp"
#include "Vector3D.h"

class Particle
{
public:
	Particle(Vector3 pos, Vector3 vel, Vector3 a, double damping, float dTime);
	~Particle();

	void integrate(double t);
	float getTime() const { return destroyTime; }

protected:
	Vector3 vel;
	Vector3 acc;
	double damping;
	float destroyTime;
	physx::PxTransform* pose;
	RenderItem* renderItem;
};

