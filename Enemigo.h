#pragma once
#include<iostream>
#include<ctime>
using namespace System::Drawing;

class Enemigo {
private:
	int x, y;
	int dx;
	int indiceW, indiceH;
	int W, H;
	bool visibilidad;

public:
	Enemigo(int W, int H) {
		this->W = W;
		this->H = H;
		this->dx = 10; // velocidad enemigo
		this->x = 640; // derecha
		this->y = rand() % 350; // posicion aleatoria
		this->indiceW = 0;
		this->indiceH = 1; //enemigo
		this->visibilidad = true;
	}

	~Enemigo() {}

	void dibujarE(Graphics^ gr, Bitmap^ bmp) {
		Rectangle porcionMostrar = Rectangle(indiceW * W, indiceH * H, W, H);
		Rectangle zoom = Rectangle(x, y, W, H);
		gr->DrawImage(bmp, zoom, porcionMostrar, GraphicsUnit::Pixel);
	}

	void moverE(Graphics^ gr) {
		x -= dx;
		indiceW++;
		if (indiceW > 3) indiceW = 0;

		if (x + W < 0) visibilidad = false; // salio de la pantalla
	}

	Rectangle getRectangle() { return Rectangle(x, y, W, H); }
	void setVisibilidad(bool v) { visibilidad = v; }
	bool getVisibilidad() { return visibilidad; }
};

