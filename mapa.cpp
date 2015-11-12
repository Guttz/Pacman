#include "mapa.h"
#include <stdlib.h>
Ambiente::Ambiente()
{
	//obtem a resolucao
	fstream fs ("config.txt", fstream::in );
	string altura, largura;
	getline(fs, altura);
	getline(fs, largura);

	altura = altura.substr(9,5);
	largura = largura.substr(9,5);


	long double a = stoi(altura, nullptr);
	long double l = stoi(largura, nullptr);

	alturaSQM = a/31;
	larguraSQM = l/28;

	restoalturaSQM = a/31 - (int) a/31;
	restolarguraSQM = l/28 - (int)l/28;

	//printf("%Lf, %Lf \n", alturaSQM, restoalturaSQM );
	//printf("%Lf, %Lf \n", larguraSQM, restolarguraSQM );
	

	fstream fs2("mapa.txt", fstream::in);
	for(int i=0; i<31; i++)
	{
		string linha;
		getline(fs2, linha);
		for(int j = 0; j < 28; j++)
		{
			matriz[i][j] = stoi(linha.substr(j,1), nullptr);
		}		
	}
	fs.close();
	fs2.close();

	//Preenchendo matriz auxiliar
		for(int cont1=0; cont1<33; cont1++)
			{
				for(int cont2=0; cont2<30; cont2++)
				{
					matrizAux[cont1][cont2] = PAREDE;
				
				}
			}

		for(int cont1=1; cont1<32; cont1++)
		{
			for(int cont2=1; cont2<29; cont2++)
			{
				matrizAux[cont1][cont2] = matriz[cont1-1][cont2-1];
			}
		}


}

void Ambiente::imprime(SDL_Renderer** render)
{
	for(int i=0, w = 1; i<31; i++, w++)
	{
		
		if(restoalturaSQMAcumulado + w*restoalturaSQM >= 1){
			restoalturaSQMAcumulado = restoalturaSQMAcumulado + w*alturaSQM;
			w = 0;
		}
		for(int j = 0, k = 1; j < 28; j++, k++)
		{
			SDL_Rect sqm;
			
			//Determinando posicao e medidas do sqm
			sqm.x = (int)j*larguraSQM;
			sqm.y = (int)i*alturaSQM;
			sqm.h = (int)alturaSQM + 1;
			sqm.w = (int)larguraSQM+ 1;

/*			if(restolarguraSQMAcumulado + k*restolarguraSQM >= 1)
			{
				restolarguraSQMAcumulado = restolarguraSQMAcumulado + k*larguraSQM;
				k = 0;
			}

			if( restolarguraSQMAcumulado >= 1)
			{
				sqm.x = (int)j*larguraSQM - 1;
				sqm.w = (int)larguraSQM + 1;
				restolarguraSQMAcumulado = restolarguraSQMAcumulado - 1;	
			}

			else
			{
				sqm.x = (int)j*larguraSQM;
				sqm.w = (int)larguraSQM;
			}

			if(restoalturaSQMAcumulado >= 1){
				sqm.y = (int)i*alturaSQM - 1;
				sqm.h = (int)alturaSQM + 1;	
			}

			else
			{
				sqm.y = (int)i*alturaSQM;	
				sqm.h = (int)alturaSQM;
			}
*/

			if(matriz[i][j] == PACMAN )
			{	
				cout << "divPacman:" << divisorDeSQM ;
				divisorDeSQM++;
				for(int iAlt = 0; iAlt < alturaSQM; iAlt++)
					for(int jLarg = 0; jLarg < larguraSQM; jLarg++)
				{
					SDL_Rect pixel = { (int) (j*larguraSQM) + jLarg, (int) (i* alturaSQM) + iAlt, 1, 1};					
					if(  pow ((jLarg - larguraSQM/2), 2) + pow ((iAlt - alturaSQM/2), 2)  < pow( 	min(alturaSQM/2, larguraSQM/2),2) ){

						//imprimindo o pacman
						SDL_SetRenderDrawColor( *render, 255, 255, 0, 0xFF );
						SDL_RenderFillRect(*render, &pixel);
					}
					else{
						SDL_SetRenderDrawColor( *render, 0, 0, 0, 0xFF );
						SDL_RenderFillRect(*render, &pixel);
					}
				}	

				if (divisorDeSQM == 4)
				{
					divisorDeSQM = 0;
				}
				
			}

			//Determinando o que será impresso no sqm
			else if(matriz[i][j] == PAREDE)
			{
				//Imprimir quadrado azul
				SDL_SetRenderDrawColor( *render, 0, 0, 255, 0xFF );
				SDL_RenderFillRect(*render, &sqm);

/*				for(int k=0; k<LARGURA+2; k++)
				{
					matrizAux[0][k] = matriz[-1][k-1];
					matrizAux[ALTURA+1][k] = matriz[ALTURA][k-1];

				}

				for(int k=0; k<ALTURA+2; k++)
				{
					matrizAux[k][0] = matriz[k-1][-1];
					matrizAux[k][LARGURA+1] = matriz[k-1][LARGURA];
				}*/

/*				if(matrizAux[i-1+1][j+1] == PAREDE)
					sqm.y = sqm.y;
				else
					sqm.y = sqm.y + 4;

				if(matrizAux[i+1][j-1+1] == PAREDE)
					sqm.x = sqm.x;
				else
					sqm.x = sqm.x + 4;

				if(matrizAux[i+1][j+1+1] == PAREDE)
					sqm.w = sqm.w;
				else
					sqm.w = sqm.w - 4;

				if(matrizAux[i+1+1][j+1] == PAREDE) 
					sqm.h = sqm.y;
				else
					sqm.y = sqm.y -4;

				SDL_SetRenderDrawColor( *render, 0, 0, 0, 0xFF );
				SDL_RenderFillRect(*render, &sqm);

				if(matrizAux[i-1+1][j+1] == PAREDE)
					sqm.y = sqm.y;
				else
					sqm.y = sqm.y + 8;

				if(matrizAux[i+1][j-1+1] == PAREDE)
					sqm.x = sqm.x;
				else
					sqm.x = sqm.x + 8;

				if(matrizAux[i+1][j+1+1] == PAREDE)
					sqm.w = sqm.w;
				else
					sqm.w = sqm.w - 8;

				if(matrizAux[i+1+1][j+1] == PAREDE) 
					sqm.h = sqm.y;
				else
					sqm.y = sqm.y -8;

				SDL_SetRenderDrawColor( *render, 0, 0, 0, 0xFF );
				SDL_RenderFillRect(*render, &sqm);*/

				if(i!=0)
				{

				if(matrizAux[i-1+1][j+1] == PAREDE)
					sqm.y = sqm.y;
				else
					sqm.y = sqm.y + 2;

				if(matrizAux[i+1][j-1+1] == PAREDE)
					sqm.x = sqm.x;
				else
					sqm.x = sqm.x + 2;

				if(matrizAux[i+1][j+1+1] == PAREDE)
					sqm.w = sqm.w;
				else
					sqm.w = sqm.w - 2;

				if(matrizAux[i+1+1][j+1] == PAREDE) 
					sqm.h = sqm.y;
				else
					sqm.y = sqm.y -2;

				SDL_SetRenderDrawColor( *render, 0, 0, 0, 0xFF );
				SDL_RenderFillRect(*render, &sqm);
				}
				else{
					if( matrizAux[i-1+1][j+1] != PAREDE || matrizAux[i+1][j-1+1] != PAREDE ||  matrizAux[i+1][j+1+1] != PAREDE || matrizAux[i+1+1][j+1] != PAREDE)
						sqm.h = sqm.h -2;

					SDL_SetRenderDrawColor( *render, 0, 0, 0, 0xFF );
					SDL_RenderFillRect(*render, &sqm);
				}
			}
			else if(matriz[i][j] == COMIDAP)
			{
				for(int iAlt = 0; iAlt < alturaSQM; iAlt++)
					for(int jLarg = 0; jLarg < larguraSQM; jLarg++)
				{
					SDL_Rect pixel = { (int) (j*larguraSQM) + jLarg, (int) (i* alturaSQM) + iAlt, 1, 1};					
					if(  pow ((jLarg - larguraSQM/2), 2) + pow ((iAlt - alturaSQM/2), 2)  < pow( min(alturaSQM/7, larguraSQM/7),2) ){

						//imprimindo o a comida pequena
						SDL_SetRenderDrawColor( *render, 255, 255, 255, 0xFF );
						SDL_RenderFillRect(*render, &pixel);
					}
					else{
						SDL_SetRenderDrawColor( *render, 0, 0, 0, 0xFF );
						SDL_RenderFillRect(*render, &pixel);
					}
				}

			}
			else if(matriz[i][j] == COMIDAG)
			{


				for(int iAlt = 0; iAlt < alturaSQM; iAlt++)
					for(int jLarg = 0; jLarg < larguraSQM; jLarg++)
				{
					SDL_Rect pixel = { (int) (j*larguraSQM) + jLarg, (int) (i* alturaSQM) + iAlt, 1, 1};					
					if(  pow ((jLarg - larguraSQM/2), 2) + pow ((iAlt - alturaSQM/2), 2)  < pow( min(alturaSQM/2.5, larguraSQM/2.5),2) ){

						//imprimindo a comida grande
						SDL_SetRenderDrawColor( *render, 255, 255, 255, 0xFF );
						SDL_RenderFillRect(*render, &pixel);
					}
					else{
						SDL_SetRenderDrawColor( *render, 0, 0, 0, 0xFF );
						SDL_RenderFillRect(*render, &pixel);
					}
				}	

			}
			else if(matriz[i][j] == VAZIO)
			{
				//Imprimindo o retangulo preto
				SDL_SetRenderDrawColor( *render, 0, 0, 0, 0xFF );
				SDL_RenderFillRect(*render, &sqm);
			}
			else if(matriz[i][j] == PAREDEFANTASMA)
			{
				//Imprimindo o retangulo branco
				SDL_SetRenderDrawColor( *render, 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderFillRect(*render, &sqm);
			}

			else if(matriz[i][j] == PORTAL)
			{

				//Imprimindo o portal rosa
				SDL_SetRenderDrawColor( *render, 255, 255, 255, 0xFF );
				SDL_RenderFillRect(*render, &sqm);
			}
			else if(matriz[i][j] == PACPORTAL)
			{
				//Imprimindo o portalcupacman rosa
				SDL_SetRenderDrawColor( *render, 250, 250, 100, 0xFF );
				SDL_RenderFillRect(*render, &sqm);
			}

		}
		if( restoalturaSQMAcumulado >= 1)
		{
			restoalturaSQMAcumulado = restolarguraSQMAcumulado - 1;	
		}
	}
}
void Ambiente::setPacman(int x, int y)
{
	matriz[x][y] = PACMAN;
}
void Ambiente::setPacPortal(int x, int y)
{
	matriz[x][y] = PACPORTAL;
}
void Ambiente::setVazio(int x, int y)
{
	matriz[x][y] = VAZIO;
}
void Ambiente::setPortal(int x, int y)
{
	matriz[x][y] = PORTAL;
}
int Ambiente::getPosicao(int x, int y)
{
	return matriz[x][y];
}
void Ambiente::getPortais(int* x1, int* y1, int* x2, int* y2)
{
	int vezes = 0;
	for(int i=0; i<31; i++)
		for(int j=0; j<28; j++)
		{
			if(matriz[i][j] == PORTAL)
			{
				if(vezes == 0)
				{
					(*x1) = i;
					(*y1) = j;
					vezes++;
				}
				else
				{
					(*x2) = i;
					(*y2) = j;
					break;
				}
			}
		}
}