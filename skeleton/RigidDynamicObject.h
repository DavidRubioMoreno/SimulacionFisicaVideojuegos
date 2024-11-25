

#pragma once

#include <PxPhysicsAPI.h>
#include "RenderUtils.hpp"

class RigidDynamicObject
{
public:
	enum ShapeType{BOX, SPHERE, PLANE, CAPSULE};
	RigidDynamicObject(physx::PxScene* scene, Vector4 color, Vector3 position, float lifeTime, Vector3 linearVelocity, ShapeType shape, Vector3 size = physx::PxVec3(5, 5, 5), float density = 1.0f,  Vector3 angularVelocity = physx::PxVec3(0,0,0));
	RigidDynamicObject(physx::PxScene* scene, Vector4 color, Vector3 position, float lifeTime, Vector3 linearVelocity, physx::PxShape* shape, float density = 1.0f, Vector3 angularVelocity = physx::PxVec3(0, 0, 0));
	void updateRigid();
	float getTime() const { return destroyTime; }
	Vector3 getPos() const { return solid->getGlobalPose().p; }
	Vector3 getVel() const { return solid->getLinearVelocity(); }
	float getHeight() const { return height; }
	void addForce(const Vector3& force);
	void addAccel(const Vector3& accel);
	void setAffectedByPhysics(bool affected);
	const Vector3 getInitPos() const { return initPosition; }
	~RigidDynamicObject();
private:
	float destroyTime;
	float density;
	physx::PxRigidDynamic* solid = nullptr;
	RenderItem* renderItem = nullptr;
	physx::PxShape* shape = nullptr;
	physx::PxScene* scene = nullptr;
	bool affectedByPhysics;
	const Vector3 initPosition;
	const float height;
};

