#include "inicializacao.h"

#ifndef vertices_H
#define vertices_H

class Vertice
{
	public:
		Vertice();
		Vertice(int x, int y);
		void setX(int x);
		int getX();
		void setY(int y);
		int getY();
		void visitadoTrue();
		bool getVisitado();
		void setDistanciaAcumulada(int distancia);
		int getDistanciaAcumulada();
		void setPaiX(int x);
		void setPaiY(int y);
		int getPaiX();
		int getPaiY();

	private:
		int posicaoX;
		int posicaoY;
		bool visitado;
		int distanciaAcumulada;
		int paiX;
		int paiY;
};

#endif /* vertices_H */