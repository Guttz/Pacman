#include "inicializacao.h"

#ifndef arestas_H
#define arestas_H

#include "vertices.h"

class Aresta
{
	public:
		Aresta();
		Aresta(Vertice origem, Vertice destino, int peso);
		void setOrigem(Vertice origem);
		Vertice* getOrigem();
		void setDestino(Vertice destino);
		Vertice* getDestino();
		int getPeso();
	private:
		Vertice origem;
		Vertice destino;
		int peso;
};

#endif /* arestas_H */