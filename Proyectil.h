#pragma once
#include <iostream>
using namespace System::Drawing;

class Proyectil {
private:
	int x, y;
	int dx;
	bool visibilidad;
public:
	Proyectil(int x, int y) {
		this->x = x;
		this->y = y;
		this->dx = 30;
		this->visibilidad = true;
	}

	~Proyectil() {}

	void mover(Graphics^ gr) {
		if (x + 10 < gr->VisibleClipBounds.Width)
			x += dx;
		else
			visibilidad = false;
	}

	void dibujar(Graphics^ gr) {
		SolidBrush^ brocha = gcnew SolidBrush(Color::Red);
		gr->FillEllipse(brocha, x, y, 10, 10); // circulo pequeño
		delete brocha;
	}
	int getX() { return x; }
	int getY() { return y; }
	bool getVisibilidad() { return visibilidad; }
	void setVisibilidad(bool v) { visibilidad = v; }
};
