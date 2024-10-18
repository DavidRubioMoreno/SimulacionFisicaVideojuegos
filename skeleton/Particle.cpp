#include "Particle.h"

using namespace physx;

Particle::Particle(Vector4 color, Vector3 pos, Vector3 vel, Vector3 a, double d, float dTime) : vel(vel), acc(a), damping(d), destroyTime(dTime), initPosition(pos) {

    pose = new physx::PxTransform(pos);
    PxSphereGeometry* geo = new PxSphereGeometry(1);
    PxShape* shape = CreateShape(*geo);

    renderItem = new RenderItem(shape, pose, color);// creamos render item

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