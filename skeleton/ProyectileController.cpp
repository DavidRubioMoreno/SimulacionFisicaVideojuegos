#include "ProyectileController.h"

ProyectileController::ProyectileController(){
}

ProyectileController::ProyectileController(Vector3 dir, Vector3 pos) : dir(dir), pos(pos) {}

void ProyectileController::addProyectile(Proyectil::ProjectileType type) {
	Proyectil* p = new Proyectil(pos, dir, DAMPING, 5, type);
	projectiles.push_back(p);
}

void ProyectileController::integrateProjectiles(double t) {
	for (auto& p : projectiles)
	{
		p->integrate(t);
	}
}

void ProyectileController::setDir(Vector3 newDir) {
	dir = newDir;
}

void ProyectileController::setPos(Vector3 newPos) {
	pos = newPos;
}

ProyectileController::~ProyectileController() {
	for (auto& p : projectiles)
	{
		delete p;
	}

	projectiles.clear();
}