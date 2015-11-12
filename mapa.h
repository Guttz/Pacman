#ifndef mapa_H
#define mapa_H

#include "inicializacao.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <math.h>  
#include <algorithm>

class Ambiente
{
	public:
		Ambiente();

		void imprime(SDL_Renderer** render);
		void setPacman(int x, int y);
		void setVazio(int x, int y);
		void setPortal(int x, int y);
		void setPacPortal(int x, int y);
		int getPosicao(int x, int y);
		void getPortais(int* x1, int* y1, int* x2, int* y2);
	private:
		int matriz[31][28];
		int matrizAux[ALTURA+2][LARGURA + 2];
		
		long double alturaSQM = 0;
		long double larguraSQM = 0;
		long double restoalturaSQM = 0;
		long double restolarguraSQM = 0;
		long double restolarguraSQMAcumulado = 0;
		long double restoalturaSQMAcumulado = 0;
		int contadora = 0;
		int divisorDeSQM = 0;

};
#endif /* mapa_H */