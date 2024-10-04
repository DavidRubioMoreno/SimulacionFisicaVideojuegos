#pragma once

#include <PxPhysicsAPI.h>
#include "RenderUtils.hpp"
#include "Vector3D.h"

class Particle
{
public:
	Particle(Vector3 pos, Vector3 vel, Vector3 a, double damping);
	~Particle();

	void integrate(double t);

protected:
	Vector3 vel;
	Vector3 acc;
	double damping;
	physx::PxTransform* pose;
	RenderItem* renderItem;
};

