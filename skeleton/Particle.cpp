#include "Particle.h"

using namespace physx;

Particle::Particle(Vector3 pos, Vector3 vel, Vector3 a, double d, float dTime) : vel(vel), acc(a), damping(d), destroyTime(dTime) {

    pose = new physx::PxTransform(pos);
    PxSphereGeometry* geo = new PxSphereGeometry(1);
    PxShape* shape = CreateShape(*geo);
    const Vector4 colorWhite = { 1, 0, 0, 1 };

    renderItem = new RenderItem(shape, pose, colorWhite);// creamos render item

}

Particle::~Particle() {//liberamos el render item
    renderItem->release();
    renderItem = nullptr;
}

void Particle::integrate(double t) {
 
    vel += acc * t; //modificamos la velocidad

    vel *= (1.0 - damping); //aplicamos damping

    pose->p += vel * t; // Actualiza la posición

}