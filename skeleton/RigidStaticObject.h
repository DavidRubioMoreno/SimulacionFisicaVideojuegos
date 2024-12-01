#pragma once

#include <PxPhysicsAPI.h>
#include "RenderUtils.hpp"

class RigidStaticObject
{
public:
	enum FormType { BOX, SPHERE, PLANE, CAPSULE};
	RigidStaticObject(physx::PxScene* scene, Vector4 color, Vector3 position, FormType shape, Vector3 size = physx::PxVec3(5, 5, 5));
	~RigidStaticObject();
	physx::PxRigidStatic* getActor() { return solid; }
private:
	physx::PxRigidStatic* solid = nullptr;
	RenderItem* renderItem = nullptr;
	physx::PxShape* shape = nullptr;
	physx::PxScene* scene = nullptr;
};

