#pragma once

#include <PxPhysicsAPI.h>
#include "RenderUtils.hpp"
#include "Vector3D.h"

class Particle
{
public:
	Particle(Vector4 color, Vector3 pos, Vector3 vel, Vector3 a, double damping, float dTime);
	~Particle();
	void integrate(double t);
	float getTime() const { return destroyTime; }
	Vector3 getPos() const { return renderItem->transform->p; }
	Vector3 getInitPos() const { return initPosition; }

protected:
	Vector3 vel;
	Vector3 acc;
	Vector3 initPosition;
	double damping;
	float destroyTime;
	physx::PxTransform* pose;
	RenderItem* renderItem;
};

