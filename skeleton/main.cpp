#include <ctype.h>

#include <PxPhysicsAPI.h>

#include <vector>
#include "Vector3D.h"

#include "core.hpp"
#include "RenderUtils.hpp"
#include "callbacks.hpp"
#include "Particle.h"
#include "ProyectileController.h"
#include "ParticleSystem.h"
#include "ParticleGenerator.h"
#include <list>

#include <iostream>

std::string display_text = "This is a test";


using namespace physx;

PxDefaultAllocator		gAllocator;
PxDefaultErrorCallback	gErrorCallback;

PxFoundation*			gFoundation = NULL;
PxPhysics*				gPhysics	= NULL;

RenderItem*       gSphereX     = NULL;
RenderItem* gSphereY = NULL;
RenderItem* gSphereZ = NULL;
RenderItem* gSphereCentre = NULL;

Particle* p = NULL;
ProyectileController* pController = NULL;
ParticleSystem* pSystem = NULL;


PxMaterial*				gMaterial	= NULL;

PxPvd*                  gPvd        = NULL;

PxDefaultCpuDispatcher*	gDispatcher = NULL;
PxScene* gScene = NULL;

ContactReportCallback gContactReportCallback;

std::list<ParticleGenerator*>::iterator generator1;

float speedIncrease = 0.0f;


// Initialize physics engine
void initPhysics(bool interactive)
{
	PX_UNUSED(interactive);

	gFoundation = PxCreateFoundation(PX_FOUNDATION_VERSION, gAllocator, gErrorCallback);

	gPvd = PxCreatePvd(*gFoundation);
	PxPvdTransport* transport = PxDefaultPvdSocketTransportCreate(PVD_HOST, 5425, 10);
	gPvd->connect(*transport,PxPvdInstrumentationFlag::eALL);

	gPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *gFoundation, PxTolerancesScale(),true,gPvd);

	gMaterial = gPhysics->createMaterial(0.5f, 0.5f, 0.6f);

	const float DISTANCE_TO_CENTRE = 10;

	const Vector3D centre;
	//Ejes
	const Vector3D X_axis(1, 0, 0 );
	const Vector3D Y_axis(0, 1, 0 );
	const Vector3D Z_axis(0, 0, 1 );


	//Transforms de los ejes
	PxTransform* t1 = new PxTransform(X_axis.getX() * DISTANCE_TO_CENTRE, X_axis.getY(), X_axis.getZ());
	PxTransform* t2 = new PxTransform(Y_axis.getX(), Y_axis.getY() * DISTANCE_TO_CENTRE, Y_axis.getZ());
	PxTransform* t3 = new PxTransform(Z_axis.getX(), Z_axis.getY(), Z_axis.getZ() * DISTANCE_TO_CENTRE);

	//Centro transform(0, 0, 0)
	PxTransform* t4 = new PxTransform(centre.getX(), centre.getY(), centre.getZ());

	//Colores
	const Vector4 colorRed = { 1, 0, 0, 1 };
	const Vector4 colorGreen = { 0, 1, 0, 1 };
	const Vector4 colorBlue = { 0, 0, 1, 1 };
	const Vector4 colorWhite = { 1, 1, 1, 1 };

	//Geometrias y formas
	PxSphereGeometry* geo = new PxSphereGeometry(PxSphereGeometry(1));
	PxShape* shape = CreateShape(*geo, gMaterial);
	
	//Items
	gSphereX = new RenderItem(shape, t1, colorRed);
	gSphereY = new RenderItem(shape, t2, colorGreen);
	gSphereZ = new RenderItem(shape, t3, colorBlue);
	//gSphereCentre = new RenderItem(shape, t4, colorWhite);

	
	//SISTEMA DE PROYECTILES
	pController = new ProyectileController();

	//SISTEMA DE PARTICULAS
	pSystem = new ParticleSystem();

	//GENERADORES PARTICULAS
	//generator1 = pSystem->addGenerator(ParticleSystem::FOG);
	//auto gen2 = pSystem->addGenerator(ParticleSystem::FOUNTAIN);
	//auto gen3 = pSystem->addGenerator(ParticleSystem::FOG);
	//auto gen4 = pSystem->addGenerator(ParticleSystem::RAIN);

	//
	//pSystem->setGeneratorPosition(gen2, Vector3(100, 0, 0));
	//pSystem->setGeneratorPosition(gen3, Vector3(-100, 0, 0));
	//pSystem->setGeneratorPosition(gen4, Vector3(200, 0, 0));

	//pSystem->setGeneratorPosition(generator1, Vector3(0, 0, 0));
	//pSystem->setGeneratorPosUniform(generator1, {-20, 20});
	//pSystem->setGeneratorParticleNumber(generator1, 10);
	//pSystem->setGeneratorSpeed(generator1, 0.1);
	//pSystem->setGeneratorColor(generator1, colorRed);

	//pSystem->setGeneratorColor(gen2, colorWhite);

	////GENERADORES DE FUERZA
	//auto fgen1 = pSystem->addForceGenerator(ParticleSystem::GRAVITY, Vector3(0, 0, 0), Vector3(0, -9.8, 0));
	//auto fgen2 = pSystem->addForceGenerator(ParticleSystem::TORNADO, Vector3(100, 0, 0), Vector3(50, 0, 0), Vector3(100, 100, 100));
	//auto fgen3 = pSystem->addForceGenerator(ParticleSystem::WIND, Vector3(200, 0, 0), Vector3(0, 1000, 0), Vector3(100, 100, 100));

	////GENERADORES A LOS QUE AFECTAN
	////pSystem->applyForceGenerator(generator1, fgen1);
	//pSystem->applyForceGenerator(gen2, fgen2);
	//pSystem->applyForceGenerator(gen4, fgen3);
	//pSystem->applyForceGenerator(gen3, fgen1);

	pSystem->generateSpring(2, 1, 30);


	// For Solid Rigids +++++++++++++++++++++++++++++++++++++
	PxSceneDesc sceneDesc(gPhysics->getTolerancesScale());
	sceneDesc.gravity = PxVec3(0.0f, -9.8f, 0.0f);
	gDispatcher = PxDefaultCpuDispatcherCreate(2);
	sceneDesc.cpuDispatcher = gDispatcher;
	sceneDesc.filterShader = contactReportFilterShader;
	sceneDesc.simulationEventCallback = &gContactReportCallback;
	gScene = gPhysics->createScene(sceneDesc);
	}


// Function to configure what happens in each step of physics
// interactive: true if the game is rendering, false if it offline
// t: time passed since last call in milliseconds
void stepPhysics(bool interactive, double t)
{
	PX_UNUSED(interactive);

	pController->integrateProjectiles(t);
	pSystem->updateGenerators(t);
	pSystem->updateParticles(t);

	//pSystem->setGeneratorVelUniform(generator1, { -speedIncrease, speedIncrease });
	//pSystem->setGeneratorColor(generator1, Vector4((1 / speedIncrease),speedIncrease, 0, 1));
	//pSystem->setGeneratorPosition(generator1, Vector3(speedIncrease, 0, 0));
	//speedIncrease+=0.001;
	

	gScene->simulate(t);
	gScene->fetchResults(true);
}

// Function to clean data
// Add custom code to the begining of the function
void cleanupPhysics(bool interactive)
{
	PX_UNUSED(interactive);

	delete pController;
	delete pSystem;



	// Rigid Body ++++++++++++++++++++++++++++++++++++++++++
	gScene->release();
	gDispatcher->release();
	// -----------------------------------------------------
	gPhysics->release();	
	PxPvdTransport* transport = gPvd->getTransport();
	gPvd->release();
	transport->release();
	
	gFoundation->release();
	}

// Function called when a key is pressed
void keyPress(unsigned char key, const PxTransform& camera)
{

	
	PX_UNUSED(camera);

	PxVec3 vectorOriginal(0, 0, -1);  // Un vector en el eje X

	// Aplicamos la rotación usando el cuaternión
	PxVec3 vectorRotado = camera.q.rotate(vectorOriginal);

	pController->setDir(vectorRotado); 
	pController->setPos(camera.p);

	//std::cout << "VECTOR: " << vectorRotado.x << ", " << vectorRotado.y << ", " << vectorRotado.z << "\n";
	//std::cout << "INIT_POS: " << camera.p.x << ", " << camera.p.y << ", " << camera.p.z << "\n";

	switch(toupper(key))
	{
	case 'G':
		pController->addProyectile(Proyectil::ProjectileType::BEACH_BALL);
		break;
	case 'H':
		pController->addProyectile(Proyectil::ProjectileType::MORTAR);
		break;
	case 'J':
		pController->addProyectile(Proyectil::ProjectileType::PROYECTILE);
		break;
	case 'E':
		pSystem->applyForceGenerator(generator1, pSystem->addForceGenerator(ParticleSystem::EXPLOSIVE, Vector3(0, 0, 0), Vector3(5000, 5000, 5000), Vector3(100, 100, 100)));
		break;
	default:
		break;
	}
}

void onCollision(physx::PxActor* actor1, physx::PxActor* actor2)
{
	PX_UNUSED(actor1);
	PX_UNUSED(actor2);
}


int main(int, const char*const*)
{
#ifndef OFFLINE_EXECUTION 
	extern void renderLoop();
	renderLoop();
#else
	static const PxU32 frameCount = 100;
	initPhysics(false);
	for(PxU32 i=0; i<frameCount; i++)
		stepPhysics(false);
	cleanupPhysics(false);
#endif

	return 0;
}