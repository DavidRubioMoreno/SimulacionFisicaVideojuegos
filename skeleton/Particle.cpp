#include "Particle.h"

using namespace physx;

Particle::Particle(Vector3 pos, Vector3 vel) : vel(vel) {

    pose = new physx::PxTransform(pos);
    PxSphereGeometry* geo = new PxSphereGeometry(1);
    PxShape* shape = CreateShape(*geo);
    const Vector4 colorWhite = { 1, 1, 1, 1 };

    renderItem = new RenderItem(shape, pose, colorWhite);

}

Particle::~Particle() {
    // Destructor logic if needed
    //delete renderItem;
}

void Particle::integrate(double t) {
     // Calcula el desplazamiento
    pose->p += vel * t; // Actualiza la posición

}