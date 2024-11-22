#include "RigidStaticObject.h"
#include "PxPhysics.h"
#include "PxScene.h"

using namespace physx;

RigidStaticObject::RigidStaticObject(physx::PxScene* scene, Vector4 color, Vector3 position, FormType shapeForm, Vector3 size) : scene(scene)
{
	solid = scene->getPhysics().createRigidStatic(PxTransform(position));
	switch (shapeForm)
	{
	case RigidStaticObject::BOX:
		shape = CreateShape(PxBoxGeometry(size));
		break;
	case RigidStaticObject::SPHERE:
		shape = CreateShape(PxSphereGeometry(size.magnitude()));
		break;
	case RigidStaticObject::PLANE:
		shape = CreateShape(PxBoxGeometry(size));
		break;
	case RigidStaticObject::CAPSULE:
		shape = CreateShape(PxCapsuleGeometry(size.x, size.y));
		break;
	default:
		break;
	}

	solid->attachShape(*shape);

	scene->addActor(*solid);

	renderItem = new RenderItem(shape, solid, color);
}

RigidStaticObject::~RigidStaticObject()
{
	if (shape != nullptr)
		shape->release();

	shape = nullptr;

	scene = nullptr;

	renderItem->release();
	renderItem = nullptr;
}
