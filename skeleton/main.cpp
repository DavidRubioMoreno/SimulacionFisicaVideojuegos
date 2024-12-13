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
#include "GameManager.h"
#include <list>

#include <iostream>

std::string display_text = "This is a test";
physx::PxVec3 window_size = { 1920,1080,0 };


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
PxMaterial* gResitantMat = NULL;
PxMaterial* gIceMat = NULL;

PxPvd*                  gPvd        = NULL;


PxActor* gFloor = NULL;

GameManager* mngr = NULL;

PxDefaultCpuDispatcher*	gDispatcher = NULL;
PxScene* gScene = NULL;

ContactReportCallback gContactReportCallback;


void onCollision(physx::PxActor* actor1, physx::PxActor* actor2){
	mngr->onCollision(actor1, actor2);
}


// Initialize physics engine
void initPhysics(bool interactive)
{
	PX_UNUSED(interactive);

	gFoundation = PxCreateFoundation(PX_FOUNDATION_VERSION, gAllocator, gErrorCallback);

	gPvd = PxCreatePvd(*gFoundation);
	PxPvdTransport* transport = PxDefaultPvdSocketTransportCreate(PVD_HOST, 5425, 10);
	gPvd->connect(*transport,PxPvdInstrumentationFlag::eALL);

	gPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *gFoundation, PxTolerancesScale(),true,gPvd);

	gMaterial = gPhysics->createMaterial(0.6f, 0.4f, 0.0f);

	gIceMat = gPhysics->createMaterial(0.1f, 0.01f, 0.2f);

	gResitantMat = gPhysics->createMaterial(0.9f, 0.5f, 1.0f);

	const float DISTANCE_TO_CENTRE = 10;

	const Vector3D centre;
	//Ejes
	const Vector3D X_axis(1, 0, 0 );
	const Vector3D Y_axis(0, 1, 0 );
	const Vector3D Z_axis(0, 0, 1 );
		
	// For Solid Rigids +++++++++++++++++++++++++++++++++++++
	PxSceneDesc sceneDesc(gPhysics->getTolerancesScale());
	sceneDesc.gravity = PxVec3(0.0f, -9.8f, 0.0f);
	gDispatcher = PxDefaultCpuDispatcherCreate(2);
	sceneDesc.cpuDispatcher = gDispatcher;
	sceneDesc.filterShader = contactReportFilterShader;
	sceneDesc.simulationEventCallback = &gContactReportCallback;
	gScene = gPhysics->createScene(sceneDesc);


	//SISTEMA DE PROYECTILES
	pController = new ProyectileController();

	//SISTEMA DE PARTICULAS
	pSystem = new ParticleSystem(gScene);

	//GAME MANAGER
	mngr = new GameManager(pSystem, GetCamera(), &window_size);

	}


// Function to configure what happens in each step of physics
// interactive: true if the game is rendering, false if it offline
// t: time passed since last call in milliseconds
void stepPhysics(bool interactive, double t)
{
	PX_UNUSED(interactive);

	mngr->update(t);
	pController->integrateProjectiles(t);
	pSystem->update(t);
	
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
	delete mngr;

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

	mngr->keyPress(key, camera);
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