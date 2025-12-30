#pragma once
#include<iostream>
using namespace System::Drawing;

class Jugador {
private:
	int x, y;
	int dx, dy;
	int indiceW, indiceH;
	int W, H;
	char direccion;
	bool destruido;

public:
	Jugador(int W, int H) : W(W), H(H), dx(0), dy(15), x(10), y(70), indiceW(0), indiceH(0), direccion('S'), destruido(false) {}

	~Jugador() {}

	void dibujar(Graphics^ gr, Bitmap^ bmp) {
		int fila = 1; // oscuro (abajo)

		if (destruido) fila = 0;         // rojo
		else if (direccion == 'W') fila = 2; // verde
		else if (direccion == 'S') fila = 1; // oscuro

		Rectangle porcionMostrar = Rectangle(indiceW * W, fila * H, W, H);
		Rectangle zoom = Rectangle(x, y, W, H);
		gr->DrawImage(bmp, zoom, porcionMostrar, GraphicsUnit::Pixel);
	}

	void mover(Graphics^ gr, char tecla) {
		if (destruido) return;

		switch (tecla) {
		case 'W':
			if (y > 0) {
				y -= dy;
				direccion = 'W';
			}
			break;
		case 'S':
			if (y + H < gr->VisibleClipBounds.Height) {
				y += dy;
				direccion = 'S';
			}
			break;
		}
		indiceW++;
		if (indiceW > 4) indiceW = 0;
	}

	char getDireccion() { return direccion; }
	int getX() { return x; }
	int getY() { return y; }
	int getW() { return W; }
	int getH() { return H; }

	void destruir() { destruido = true; }
};
