#include "Proyectil.h"

std::vector<std::pair<float, float>> bulletData = {
	{400, 0.008},   // Pistola (9mm): Velocidad 400 m/s, Peso 8g
	{1750, 7},      // Proyectil de tanque (APFSDS): Velocidad 1750 m/s, Peso 7kg
	{300, 2}        // Mortero 60mm: Velocidad 300 m/s, Peso 2kg
};

Proyectil::Proyectil(Vector3 pos, double damping, float scaleFactor, ProjectileType type)
	: Particle::Particle(pos, Vector3(bulletData[type].first, 0, 0), Vector3(0, GRAVITY, 0), damping), scaleFactor(scaleFactor), type(type)
{

	adjustMass(scaleFactor);
	adjustGravity(scaleFactor);

	std::cout << "Speed: " << vel.x << " NewMass: " << mass << " Gravedad: "<< acc.y << "\n";
}

Proyectil::~Proyectil() {

}

void Proyectil::adjustMass(float scale) {
	float module = vel.magnitude();
	mass = bulletData[type].second * ((module * module) / ((module / scale) * (module / scale)));
	vel = vel / scaleFactor;
}

void Proyectil::adjustGravity(float scale) {
	float module = vel.magnitude();
	acc.y = ((module / scale) * (module / scale)) * (GRAVITY / (module * module));
}