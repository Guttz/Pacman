#include "inicializacao.h"

#ifndef pacman_H
#define pacman_H

#include "mapa.h"

#define CIMA 1
#define BAIXO 2
#define ESQUERDA 3
#define DIREITA 4

#define ZIKA 99
class Pacman
{
	public:
		Pacman(int x, int y);
		void mover(Ambiente* mapa, SDL_Event* e);
		void evento(int valor);
		int getX();
		int getY();
		void setX(int x);
		void setY(int y);
	private:
		Mix_Chunk *somComidaPequena;
		int ultimoSentido;
		int posicaoX;
		int posicaoY;
		int estado;
		int tempoDeForca;
		int pontuacao;
		int vidas;
		Uint32 intervaloDeSomComidaPequena;
};

#endif /* pacman_H */