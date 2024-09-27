#pragma once

#include <PxPhysicsAPI.h>
#include "RenderUtils.hpp"
#include "Vector3D.h"

class Particle
{
public:
	Particle(Vector3 pos, Vector3 vel);
	~Particle();

	void integrate(double t);

private:
	Vector3 vel;
	physx::PxTransform* pose;
	RenderItem* renderItem;
};

