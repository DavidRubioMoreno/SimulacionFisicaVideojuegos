#include "RigidDynamicObject.h"
#include "PxPhysics.h"
#include "PxScene.h"

using namespace physx;

RigidDynamicObject::RigidDynamicObject(physx::PxScene* scene, Vector4 color, Vector3 position, float lifeTime, Vector3 linearVelocity, ShapeType shapeForm, Vector3 size, float density, Vector3 angularVelocity)
	: destroyTime(lifeTime), density(density), scene(scene)
{
	switch (shapeForm)
	{
	case RigidDynamicObject::BOX:
		shape = CreateShape(PxBoxGeometry(size));
		break;
	case RigidDynamicObject::SPHERE:
		shape = CreateShape(PxSphereGeometry(size.magnitude()));
		break;
	case RigidDynamicObject::PLANE:
		shape = CreateShape(PxBoxGeometry(size));
		break;
	default:
		break;
	}

	solid = scene->getPhysics().createRigidDynamic(PxTransform(position));
	solid->setLinearVelocity(linearVelocity);
	solid->setAngularVelocity(angularVelocity);

	if (shape != nullptr)
		solid->attachShape(*shape);

	PxRigidBodyExt::updateMassAndInertia(*solid, density);

	scene->addActor(*solid);

	renderItem = new RenderItem(shape, solid, color);
}

RigidDynamicObject::RigidDynamicObject(physx::PxScene* scene, Vector4 color, Vector3 position, float lifeTime, Vector3 linearVelocity, physx::PxShape* shape, float density, Vector3 angularVelocity)
	: destroyTime(lifeTime), density(density), scene(scene)
{
	solid = scene->getPhysics().createRigidDynamic(PxTransform(position));
	solid->setLinearVelocity(linearVelocity);
	solid->setAngularVelocity(angularVelocity);

	solid->attachShape(*shape);

	PxRigidBodyExt::updateMassAndInertia(*solid, density);

	scene->addActor(*solid);

	renderItem = new RenderItem(shape, solid, color);
}

void RigidDynamicObject::updateRigid()
{
	PxRigidBodyExt::updateMassAndInertia(*solid, density);
}

RigidDynamicObject::~RigidDynamicObject()
{
	if (shape != nullptr)
		shape->release();

	shape = nullptr;

	scene = nullptr;

	renderItem->release();
	renderItem = nullptr;
}
