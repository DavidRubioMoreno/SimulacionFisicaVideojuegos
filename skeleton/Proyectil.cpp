#include "Proyectil.h"

std::vector<std::pair<float, float>> bulletData = {
	{400, 0.008},   // Pistola (9mm): Velocidad 400 m/s, Peso 8g
	{1750, 7},      // Proyectil de tanque (APFSDS): Velocidad 1750 m/s, Peso 7kg
	{300, 2},        // Mortero 60mm: Velocidad 300 m/s, Peso 2kg
	{25, 0.05}       //Pelota de playa  
};

Proyectil::Proyectil(Vector3 pos, Vector3 dir, double damping, float scaleFactor, ProjectileType type)
	: Particle::Particle(Vector4(1, 1, 1, 1), pos, (dir / dir.magnitude()) * bulletData[type].first, Vector3(0, GRAVITY, 0), damping, 1000), scaleFactor(scaleFactor), type(type)
{

	adjustMass(scaleFactor);
	adjustGravity(scaleFactor);

	std::cout << "Speed: " << vel.magnitude() << " NewMass: " << mass << " Gravedad: "<< acc.y << "\n";
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