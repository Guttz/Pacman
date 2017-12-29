#include "arestas.h"
Aresta::Aresta()
{
	Vertice novo(0,0);
	this->origem = novo;
	this->destino = novo;
	this->peso = 0;
}
Aresta::Aresta(Vertice origem, Vertice destino, int peso)
{
	this->origem = origem;
	this->destino = destino;
	this->peso = peso;
}
void  Aresta::setOrigem(Vertice origem)
{
	this->origem = origem;
}
Vertice*  Aresta::getOrigem()
{
	return &(this->origem);
}
void  Aresta::setDestino(Vertice destino)
{
	this->destino = destino;
}
Vertice*  Aresta::getDestino()
{
	return &(this->destino);
}
int Aresta::getPeso()
{
	return this->peso;
}