#include "RigidDynamicObject.h"
#include "PxPhysics.h"
#include "PxScene.h"


using namespace physx;

RigidDynamicObject::RigidDynamicObject(physx::PxScene* scene, Vector4 color, Vector3 position, float lifeTime,
	Vector3 linearVelocity, ShapeType shapeForm, Vector3 size, float density, Vector3 angularVelocity)
	: destroyTime(lifeTime), density(density), scene(scene), initPosition(position), height(size.magnitude() / 2), affectedByPhysics(true)
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
	case RigidDynamicObject::CAPSULE:
		shape = CreateShape(PxCapsuleGeometry(size.x, size.y));
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

RigidDynamicObject::RigidDynamicObject(physx::PxScene* scene, Vector4 color, Vector3 position, float lifeTime, 
	Vector3 linearVelocity, physx::PxShape* shape, ParticleGenerator* gen, float density, Vector3 angularVelocity)
	: destroyTime(lifeTime), density(density), scene(scene), initPosition(position), height(5.0), affectedByPhysics(true), generator(gen)
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

void RigidDynamicObject::addForce(const Vector3& force)
{
	solid->addForce(force);
}

void RigidDynamicObject::addAccel(const Vector3& accel)
{
	solid->addForce(accel, PxForceMode::eACCELERATION);
}

void RigidDynamicObject::addSub(std::list<RigidDynamicObject*>::iterator sub)
{
	subs.push_back(sub);
}

void RigidDynamicObject::setAffectedByPhysics(bool affected)
{
	if (affected && !affectedByPhysics) {
		scene->addActor(*solid);
		affectedByPhysics = affected;
	}
	else if (!affected && affectedByPhysics) {
		scene->removeActor(*solid);
		affectedByPhysics = affected;
	}
}

RigidDynamicObject::~RigidDynamicObject()
{
	if (shape != nullptr)
		shape->release();

	shape = nullptr;

	if(affectedByPhysics)scene->removeActor(*solid);
	solid->release();
	solid = nullptr;

	scene = nullptr;

	renderItem->release();
	renderItem = nullptr;

	subs.clear();
}
