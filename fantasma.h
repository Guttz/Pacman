#include "inicializacao.h"

#ifndef fantasma_H
#define fantasma_H

#include <list>
#include "vertices.h"
#include "arestas.h"
#include "mapa.h"

class Fantasma
{
	public:
		Fantasma(int x, int y);
		void mover(Ambiente* mapa);
		int getX();
		int getY();
		void setX(int x);
		void setY(int y);
	private:
		int posicaoX;
		int posicaoY;

};

#endif /* fantasma_H */