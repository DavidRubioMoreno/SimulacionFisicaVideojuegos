#include "ProyectileController.h"


void ProyectileController::addProyectile(Proyectil::ProjectileType type, Vector3 pos, Vector3 dir) {
	projectiles.push_back(new Proyectil(pos, DAMPING, 100, type));
}

void ProyectileController::integrateProjectiles(double t) {
	for (auto& p : projectiles)
	{
		p->integrate(t);
	}
}

ProyectileController::~ProyectileController() {

}