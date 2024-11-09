#include "Particle.h"
#include "ParticleGenerator.h"

using namespace physx;

Particle::Particle(Vector4 color, Vector3 pos, Vector3 vel, Vector3 a, double d, float dTime)
    : vel(vel), acc(a), damping(d), destroyTime(dTime), initPosition(pos) 
{

    pose = new physx::PxTransform(pos);
    PxSphereGeometry* geo = new PxSphereGeometry(1);
    PxShape* shape = CreateShape(*geo);

    renderItem = new RenderItem(shape, pose, color);// creamos render item

}

Particle::Particle(Vector4 color, Vector3 pos, Vector3 vel, Vector3 a, double d, float dTime, ParticleGenerator* gen, PxShape* shape)
    : vel(vel), acc(a), damping(d), destroyTime(dTime), initPosition(pos), generator(gen)
{

    pose = new physx::PxTransform(pos);
    renderItem = new RenderItem(shape, pose, color);// creamos render item

}

Particle::~Particle() {//liberamos el render item
    renderItem->release();
    renderItem = nullptr;
    subs.clear();
}

void Particle::integrate(double t) {
 
    vel += acc * t; //modificamos la velocidad

    vel *= (1.0 - damping); //aplicamos damping

    pose->p += vel * t; // Actualiza la posición

}

void Particle::setMass(float m)
{
    mass = m;
}

void Particle::addPuntualForce(Vector3 force)
{
    acc += force;
}

void Particle::addMass(float m)
{
    mass += m;
}

void Particle::addForce(Vector3 force)
{
    acc = force / mass;
}

void Particle::addAccel(Vector3 accel, double t) {
    vel += accel * t;
}

void Particle::addSub(std::list<Particle*>::iterator id)
{
    subs.push_back(id);
}
