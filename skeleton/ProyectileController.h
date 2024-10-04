#pragma once

#include "Proyectil.h"

class ProyectileController
{
public:
	ProyectileController() = default;
	~ProyectileController();

private:
	const double DAMPING = 0.0001;
	void integrateProjectiles(double t);
	void addProyectile(Proyectil::ProjectileType type, Vector3 pos, Vector3 dir);
	std::vector<Proyectil*> projectiles;
};

