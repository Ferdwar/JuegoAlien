#pragma once
#include "Jugador.h"
#include "Proyectil.h"
#include "Enemigo.h"
#include <vector>
#include <ctime>
using namespace std;

class Controladora {
private:
	Jugador* jugador;
	vector<Proyectil*> arrProyectiles;
	vector<Enemigo*> arrEnemigos;
	time_t tiempoUltimoEnemigo;

public:
	Controladora(Bitmap^ bmpJugador) {
		tiempoUltimoEnemigo = time(NULL);
		jugador = new Jugador(bmpJugador->Width / 5, bmpJugador->Height / 3);
	}

	~Controladora() {
		delete jugador;
		for (auto p : arrProyectiles) delete p;
		for (auto e : arrEnemigos) delete e;
	}

	void moverJugador(Graphics^ gr, char tecla) {
		jugador->mover(gr, tecla);
	}

	void disparar() {
		int px = jugador->getX() + 20;
		int py = jugador->getY() + 10;
		arrProyectiles.push_back(new Proyectil(px, py));
	}

	void agregarEnemigo(int W, int H) {
		arrEnemigos.push_back(new Enemigo(W, H));
	}

	void generarEnemigoCada3Segundos(int W, int H) {
		time_t tiempoActual = time(NULL);
		if (difftime(tiempoActual, tiempoUltimoEnemigo) >= 3) {
			agregarEnemigo(W, H);
			tiempoUltimoEnemigo = tiempoActual;
		}
	}

	void dibujarTodo(Graphics^ gr, Bitmap^ bmpJugador, Bitmap^ bmpEnemigo) {
		for (auto p : arrProyectiles) p->dibujar(gr);
		for (auto e : arrEnemigos) e->dibujarE(gr, bmpEnemigo);
		jugador->dibujar(gr, bmpJugador);
	}

	void moverTodo(Graphics^ gr) {
		for (auto p : arrProyectiles) p->mover(gr);
		for (auto e : arrEnemigos) e->moverE(gr);
	}

	void colision(Graphics^ gr) {
		// proyectil vs enemigo
		for (int i = 0; i < arrProyectiles.size(); i++) {
			for (int j = 0; j < arrEnemigos.size(); j++) {
				Rectangle rProj = Rectangle(arrProyectiles[i]->getX(), arrProyectiles[i]->getY(), 10, 10);
				if (rProj.IntersectsWith(arrEnemigos[j]->getRectangle())) {
					arrProyectiles[i]->setVisibilidad(false);
					arrEnemigos[j]->setVisibilidad(false);
				}
			}
		}

		// enemigo vs jugador
		for (int i = 0; i < arrEnemigos.size(); i++) {
			if (arrEnemigos[i]->getRectangle().IntersectsWith(Rectangle(jugador->getX(), jugador->getY(), jugador->getW(), jugador->getH()))) {
				jugador->destruir(); //  pierde
			}
		}

		// limpiar proyectiles
		for (int i = 0; i < arrProyectiles.size(); i++) {
			if (!arrProyectiles[i]->getVisibilidad()) {
				delete arrProyectiles[i];
				arrProyectiles.erase(arrProyectiles.begin() + i);
				i--;
			}
		}

		// limpiar enemigos
		for (int i = 0; i < arrEnemigos.size(); i++) {
			if (!arrEnemigos[i]->getVisibilidad()) {
				delete arrEnemigos[i];
				arrEnemigos.erase(arrEnemigos.begin() + i);
				i--;
			}
		}
	}
};
