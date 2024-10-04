#pragma once

#include "Proyectil.h"

class ProyectileController
{
public:
	ProyectileController();
	ProyectileController(Vector3 dir, Vector3 pos);
	~ProyectileController();
	void integrateProjectiles(double t);
	void addProyectile(Proyectil::ProjectileType type);
	void setDir(Vector3 dir);
	void setPos(Vector3 pos);
private:
	const double DAMPING = 0.0000001;
	std::vector<Proyectil*> projectiles;
	Vector3 dir = Vector3(0, 0, 0);
	Vector3 pos = Vector3(0, 0, 0);
	
};

