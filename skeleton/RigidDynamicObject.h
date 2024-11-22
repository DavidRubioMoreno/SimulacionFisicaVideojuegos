

#pragma once

#include <PxPhysicsAPI.h>
#include "RenderUtils.hpp"

class RigidDynamicObject
{
public:
	enum ShapeType{BOX, SPHERE, PLANE};
	RigidDynamicObject(physx::PxScene* scene, Vector4 color, Vector3 position, float lifeTime, Vector3 linearVelocity, ShapeType shape, Vector3 size = physx::PxVec3(5, 5, 5), float density = 1.0f,  Vector3 angularVelocity = physx::PxVec3(0,0,0));
	RigidDynamicObject(physx::PxScene* scene, Vector4 color, Vector3 position, float lifeTime, Vector3 linearVelocity, physx::PxShape* shape, float density = 1.0f, Vector3 angularVelocity = physx::PxVec3(0, 0, 0));
	void updateRigid();
	~RigidDynamicObject();
private:
	float destroyTime;
	float density;
	physx::PxRigidDynamic* solid = nullptr;
	RenderItem* renderItem = nullptr;
	physx::PxShape* shape = nullptr;
	physx::PxScene* scene = nullptr;
};

