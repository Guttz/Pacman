#include "vertices.h"
Vertice::Vertice()
{
	this->posicaoX = 0;
	this->posicaoY = 0;
	this->visitado = false;
	this->distanciaAcumulada = 9999;
}
Vertice::Vertice(int x, int y)
{
	this->posicaoX = x;
	this->posicaoY = y;
	this->visitado = false;
	this->distanciaAcumulada = 9999;
}
void  Vertice::setX(int x)
{
	this->posicaoX = x;
}
int  Vertice::getX()
{
	return this->posicaoX;
}
void  Vertice::setY(int y)
{
	this->posicaoY = y;
}
int  Vertice::getY()
{
	return this->posicaoY;
}
void Vertice::visitadoTrue()
{
	this->visitado = true;
}
void Vertice::setDistanciaAcumulada(int distancia)
{
	this->distanciaAcumulada = distancia;
}
int Vertice::getDistanciaAcumulada()
{
	return this->distanciaAcumulada;
}
void Vertice::setPaiX(int x)
{
	this->paiX = x;
}
void Vertice::setPaiY(int y)
{
	this->paiY = y;
}
int Vertice::getPaiX()
{
	return this->paiX;
}
int Vertice::getPaiY()
{
	return this->paiY;
}
bool Vertice::getVisitado()
{
	return this->visitado;
}