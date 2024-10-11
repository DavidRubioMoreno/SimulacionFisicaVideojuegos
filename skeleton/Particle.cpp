#include "Particle.h"

using namespace physx;

Particle::Particle(Vector3 pos, Vector3 vel, Vector3 a, double d, float dTime) : vel(vel), acc(a), damping(d), destroyTime(dTime) {

    pose = new physx::PxTransform(pos);
    PxSphereGeometry* geo = new PxSphereGeometry(1);
    PxShape* shape = CreateShape(*geo);
    const Vector4 colorWhite = { 1, 1, 1, 1 };

    renderItem = new RenderItem(shape, pose, colorWhite);

}

Particle::~Particle() {

}

void Particle::integrate(double t) {
     // Calcula el desplazamiento
    vel += acc * t;

    vel *= (1.0 - damping);

    pose->p += vel * t; // Actualiza la posición

}