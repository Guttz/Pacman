#include "pacman.h"

Pacman::Pacman(int x, int y)
{
	ultimoSentido = 0;
	pontuacao = 0;
	posicaoX = x;
	posicaoY = y;

}

void Pacman::mover(Ambiente* mapa, SDL_Event* e)
{
	
	int penultimoSentido = ultimoSentido;
	if((*e).key.keysym.sym == SDLK_d || (*e).key.keysym.sym == SDLK_RIGHT)
	{
		ultimoSentido = DIREITA;
		//printf("DIREITA\n");
	}
	else if((*e).key.keysym.sym == SDLK_s || (*e).key.keysym.sym == SDLK_DOWN)
	{
		ultimoSentido = BAIXO;
		//printf("BAIXO\n");
	}
	else if((*e).key.keysym.sym == SDLK_a || (*e).key.keysym.sym == SDLK_LEFT)
	{
		ultimoSentido = ESQUERDA;
		//printf("ESQUERDA\n");
	}
	else if((*e).key.keysym.sym == SDLK_w || (*e).key.keysym.sym == SDLK_UP)
	{
		ultimoSentido = CIMA;
		//printf("CIMA\n");
	}
	
	
	if(ultimoSentido == ESQUERDA)
	{	
		evento((*mapa).getPosicao(posicaoX, posicaoY-1));
		if((*mapa).getPosicao(posicaoX, posicaoY-1)!= PAREDE && (*mapa).getPosicao(posicaoX,posicaoY-1) != PORTAL)
		{
			if((*mapa).getPosicao(posicaoX, posicaoY) == PACPORTAL)
				(*mapa).setPortal(posicaoX, posicaoY);
			else
				(*mapa).setVazio(posicaoX,posicaoY);
			(*mapa).setPacman(posicaoX, posicaoY-1);

			posicaoY--;
		}
		else if((*mapa).getPosicao(posicaoX,posicaoY-1) == PORTAL)
		{
			int x1,x2,y1,y2;
			(*mapa).getPortais(&x1,&y1,&x2,&y2);

			if(y1 == posicaoX)
			{
				(*mapa).setPacPortal(x1,y1);
				if((*mapa).getPosicao(posicaoX, posicaoY) == PORTAL)
					(*mapa).setPacPortal(x1,y1);
				else
					(*mapa).setVazio(posicaoX,posicaoY);
				posicaoX = x1;
				posicaoY = y1;
			}
			else
			{
				(*mapa).setPacPortal(x2,y2);
				if((*mapa).getPosicao(posicaoX, posicaoY) == PORTAL)
					(*mapa).setPacPortal(x2,y2);
				else
					(*mapa).setVazio(posicaoX,posicaoY);
				posicaoX = x2;
				posicaoY = y2;
			}
			
		}
		else
		{
			ultimoSentido = penultimoSentido;
			(*e).type = SDL_KEYDOWN;
			if(ultimoSentido == DIREITA)
				(*e).key.keysym.sym = SDLK_d;
			else if(ultimoSentido == BAIXO)
				(*e).key.keysym.sym = SDLK_s;
			else if(ultimoSentido == ESQUERDA)
				(*e).key.keysym.sym = SDLK_a;
			else
				(*e).key.keysym.sym = SDLK_w;
		}

	}

	if(ultimoSentido == BAIXO )
	{
		evento((*mapa).getPosicao(posicaoX+1,posicaoY));
		if(((*mapa).getPosicao(posicaoX+1,posicaoY) != PAREDE)&& (*mapa).getPosicao(posicaoX+1,posicaoY) != PORTAL)
		{

				if((*mapa).getPosicao(posicaoX, posicaoY) == PACPORTAL)
					(*mapa).setPortal(posicaoX, posicaoY);
				else
					(*mapa).setVazio(posicaoX,posicaoY);
				(*mapa).setPacman(posicaoX+1, posicaoY);
				posicaoX++;
		}
		else if((*mapa).getPosicao(posicaoX,posicaoY+1) == PORTAL)
		{
			int x1,x2,y1,y2;
			(*mapa).getPortais(&x1,&y1,&x2,&y2);

			if(y1 == posicaoX)
			{
				(*mapa).setPacPortal(x1,y1);
				if((*mapa).getPosicao(posicaoX, posicaoY) == PORTAL)
					(*mapa).setPacPortal(x1,y1);
				else
					(*mapa).setVazio(posicaoX,posicaoY);
				posicaoX = x1;
				posicaoY = y1;
			}
			else
			{
				(*mapa).setPacPortal(x2,y2);
				if((*mapa).getPosicao(posicaoX, posicaoY) == PORTAL)
					(*mapa).setPacPortal(x2,y2);
				else
					(*mapa).setVazio(posicaoX,posicaoY);
				posicaoX = x2;
				posicaoY = y2;
			}
		}
		else
		{
			ultimoSentido = penultimoSentido;
			(*e).type = SDL_KEYDOWN;
			if(ultimoSentido == DIREITA)
				(*e).key.keysym.sym = SDLK_d;
			else if(ultimoSentido == BAIXO)
				(*e).key.keysym.sym = SDLK_s;
			else if(ultimoSentido == ESQUERDA)
				(*e).key.keysym.sym = SDLK_a;
			else
				(*e).key.keysym.sym = SDLK_w;
			if(ultimoSentido == ESQUERDA)
			{
				evento((*mapa).getPosicao(posicaoX, posicaoY-1));
				if((*mapa).getPosicao(posicaoX, posicaoY-1)!= PAREDE && (*mapa).getPosicao(posicaoX,posicaoY-1) != PORTAL)
				{
					(*mapa).setPacman(posicaoX, posicaoY-1);
					if((*mapa).getPosicao(posicaoX, posicaoY) == PACPORTAL)
						(*mapa).setPortal(posicaoX, posicaoY);
					else
						(*mapa).setVazio(posicaoX,posicaoY);
					posicaoY--;
				}
				else if((*mapa).getPosicao(posicaoX,posicaoY-1) == PORTAL)
				{
					int x1,x2,y1,y2;
					(*mapa).getPortais(&x1,&y1,&x2,&y2);

					if(y1 == posicaoX)
					{
						(*mapa).setPacPortal(x1,y1);
						if((*mapa).getPosicao(posicaoX, posicaoY) == PORTAL)
							(*mapa).setPacPortal(x1,y1);
						else
							(*mapa).setVazio(posicaoX,posicaoY);
						posicaoX = x1;
						posicaoY = y1;
					}
					else
					{
						(*mapa).setPacPortal(x2,y2);
						if((*mapa).getPosicao(posicaoX, posicaoY) == PORTAL)
							(*mapa).setPacPortal(x2,y2);
						else
							(*mapa).setVazio(posicaoX,posicaoY);
						posicaoX = x2;
						posicaoY = y2;
					}
				}
			}
		}
	}

	if(ultimoSentido == DIREITA)
	{
		evento((*mapa).getPosicao(posicaoX,posicaoY+1));
		if(((*mapa).getPosicao(posicaoX,posicaoY+1) != PAREDE)&& (*mapa).getPosicao(posicaoX,posicaoY+1) != PORTAL)
		{
			if((*mapa).getPosicao(posicaoX, posicaoY) == PACPORTAL)
				(*mapa).setPortal(posicaoX, posicaoY);
			else
				(*mapa).setVazio(posicaoX,posicaoY);
			(*mapa).setPacman(posicaoX, posicaoY+1);
			posicaoY++;
		}
		else if((*mapa).getPosicao(posicaoX,posicaoY+1) == PORTAL)
		{
			int x1,x2,y1,y2;
			(*mapa).getPortais(&x1,&y1,&x2,&y2);

			if(y1 == posicaoX)
			{
				(*mapa).setPacPortal(x2,y2);
				if((*mapa).getPosicao(posicaoX, posicaoY) == PORTAL)
					(*mapa).setPacPortal(x2,y2);
				else
					(*mapa).setVazio(posicaoX,posicaoY);
				posicaoX = x2;
				posicaoY = y2;
			}
			else
			{
				(*mapa).setPacPortal(x1,y1);
				if((*mapa).getPosicao(posicaoX, posicaoY) == PORTAL)
					(*mapa).setPacPortal(x1,y1);
				else
					(*mapa).setVazio(posicaoX,posicaoY);
				posicaoX = x1;
				posicaoY = y1;
			}
		}
		else
		{
			ultimoSentido = penultimoSentido;
			(*e).type = SDL_KEYDOWN;
			if(ultimoSentido == DIREITA)
				(*e).key.keysym.sym = SDLK_d;
			else if(ultimoSentido == BAIXO)
				(*e).key.keysym.sym = SDLK_s;
			else if(ultimoSentido == ESQUERDA)
				(*e).key.keysym.sym = SDLK_a;
			else
				(*e).key.keysym.sym = SDLK_w;

			if(ultimoSentido == ESQUERDA)
			{
				evento((*mapa).getPosicao(posicaoX, posicaoY-1));
				if((*mapa).getPosicao(posicaoX, posicaoY-1)!= 1 && (*mapa).getPosicao(posicaoX,posicaoY-1) != PORTAL)
				{
					if((*mapa).getPosicao(posicaoX, posicaoY) == PACPORTAL)
						(*mapa).setPortal(posicaoX, posicaoY);
					else
						(*mapa).setVazio(posicaoX,posicaoY);
					(*mapa).setPacman(posicaoX, posicaoY-1);
					posicaoY--;
				}
				else if((*mapa).getPosicao(posicaoX,posicaoY-1) == PORTAL)
				{

					int x1,x2,y1,y2;
					(*mapa).getPortais(&x1,&y1,&x2,&y2);
					if(y1 == posicaoX)
					{
						(*mapa).setPacPortal(x1,y1);
						if((*mapa).getPosicao(posicaoX, posicaoY) == PORTAL)
							(*mapa).setPacPortal(x1,y1);
						else
							(*mapa).setVazio(posicaoX,posicaoY);
						posicaoX = x1;
						posicaoY = y1;
					}
					else
					{
						(*mapa).setPacPortal(x2,y2);
						if((*mapa).getPosicao(posicaoX, posicaoY) == PORTAL)
							(*mapa).setPacPortal(x2,y2);
						else
							(*mapa).setVazio(posicaoX,posicaoY);
						posicaoX = x2;
						posicaoY = y2;
					}
				}
			}
			else if(ultimoSentido == BAIXO)
			{
				evento((*mapa).getPosicao(posicaoX+1,posicaoY));
				if(((*mapa).getPosicao(posicaoX+1,posicaoY) != 1) && (*mapa).getPosicao(posicaoX+1,posicaoY) != PORTAL)
				{

					if((*mapa).getPosicao(posicaoX, posicaoY) == PACPORTAL)
						(*mapa).setPortal(posicaoX, posicaoY);
					else
						(*mapa).setVazio(posicaoX,posicaoY);
					(*mapa).setPacman(posicaoX+1, posicaoY);
					posicaoX++;
				}
				else if((*mapa).getPosicao(posicaoX,posicaoY+1) == PORTAL)
				{
					int x1,x2,y1,y2;
					(*mapa).getPortais(&x1,&y1,&x2,&y2);

					if(y1 == posicaoX)
					{
						(*mapa).setPacPortal(x1,y1);
						if((*mapa).getPosicao(posicaoX, posicaoY) == PORTAL)
							(*mapa).setPacPortal(x1,y1);
						else
							(*mapa).setVazio(posicaoX,posicaoY);
						posicaoX = x1;
						posicaoY = y1;
					}
					else
					{
						(*mapa).setPacPortal(x2,y2);
						if((*mapa).getPosicao(posicaoX, posicaoY) == PORTAL)
							(*mapa).setPacPortal(x2,y2);
						else
							(*mapa).setVazio(posicaoX,posicaoY);
						posicaoX = x2;
						posicaoY = y2;
					}
				}
			}
		}
	}

	if(ultimoSentido == CIMA)
	{
		evento((*mapa).getPosicao(posicaoX-1,posicaoY));
		if(((*mapa).getPosicao(posicaoX-1,posicaoY) != PAREDE)&& (*mapa).getPosicao(posicaoX-1,posicaoY) != PORTAL)
		{
			if((*mapa).getPosicao(posicaoX, posicaoY) == PACPORTAL)
				(*mapa).setPortal(posicaoX, posicaoY);
			else
				(*mapa).setVazio(posicaoX,posicaoY);
			(*mapa).setPacman(posicaoX-1, posicaoY);
			posicaoX--;
		}
		else if((*mapa).getPosicao(posicaoX-1,posicaoY) == PORTAL)
		{
			int x1,x2,y1,y2;
			(*mapa).getPortais(&x1,&y1,&x2,&y2);

			if(y1 == posicaoX)
			{
				(*mapa).setPacPortal(x1,y1);
				if((*mapa).getPosicao(posicaoX, posicaoY) == PORTAL)
					(*mapa).setPacPortal(x1,y1);
				else
					(*mapa).setVazio(posicaoX,posicaoY);
				posicaoX = x1;
				posicaoY = y1;
			}
			else
			{
				(*mapa).setPacPortal(x2,y2);
				if((*mapa).getPosicao(posicaoX, posicaoY) == PORTAL)
					(*mapa).setPacPortal(x2,y2);
				else
					(*mapa).setVazio(posicaoX,posicaoY);
				posicaoX = x2;
				posicaoY = y2;
			}
		}
		else
		{
			ultimoSentido = penultimoSentido;
			(*e).type = SDL_KEYDOWN;
			if(ultimoSentido == DIREITA)
				(*e).key.keysym.sym = SDLK_d;
			else if(ultimoSentido == BAIXO)
				(*e).key.keysym.sym = SDLK_s;
			else if(ultimoSentido == ESQUERDA)
				(*e).key.keysym.sym = SDLK_a;
			else
				(*e).key.keysym.sym = SDLK_w;

			if(ultimoSentido == ESQUERDA)
			{
				evento((*mapa).getPosicao(posicaoX, posicaoY-1));
				if((*mapa).getPosicao(posicaoX, posicaoY-1)!= PAREDE && (*mapa).getPosicao(posicaoX,posicaoY-1) != PORTAL)
				{
					if((*mapa).getPosicao(posicaoX, posicaoY) == PACPORTAL)
						(*mapa).setPortal(posicaoX, posicaoY);
					else
						(*mapa).setVazio(posicaoX,posicaoY);
					(*mapa).setPacman(posicaoX, posicaoY-1);
					posicaoY--;
				}
				else if((*mapa).getPosicao(posicaoX,posicaoY-1) == PORTAL)
				{
					int x1,x2,y1,y2;
					(*mapa).getPortais(&x1,&y1,&x2,&y2);

					if(y1 == posicaoX)
					{
						(*mapa).setPacPortal(x1,y1);
						if((*mapa).getPosicao(posicaoX, posicaoY) == PORTAL)
							(*mapa).setPacPortal(x1,y1);
						else
							(*mapa).setVazio(posicaoX,posicaoY);
						posicaoX = x1;
						posicaoY = y1;
					}
					else
					{
						(*mapa).setPacPortal(x2,y2);
						if((*mapa).getPosicao(posicaoX, posicaoY) == PORTAL)
							(*mapa).setPacPortal(x2,y2);
						else
							(*mapa).setVazio(posicaoX,posicaoY);
						posicaoX = x2;
						posicaoY = y2;
					}
				}
			}
			else if(ultimoSentido == BAIXO)
			{
				evento((*mapa).getPosicao(posicaoX+1,posicaoY));
				if(((*mapa).getPosicao(posicaoX+1,posicaoY) != PAREDE)&& (*mapa).getPosicao(posicaoX+1,posicaoY) != PORTAL)
				{

					if((*mapa).getPosicao(posicaoX, posicaoY) == PACPORTAL)
						(*mapa).setPortal(posicaoX, posicaoY);
					else
						(*mapa).setVazio(posicaoX,posicaoY);
					(*mapa).setPacman(posicaoX+1, posicaoY);
					posicaoX++;
				}
				else if((*mapa).getPosicao(posicaoX+1,posicaoY) == PORTAL)
				{
					int x1,x2,y1,y2;
					(*mapa).getPortais(&x1,&y1,&x2,&y2);

					if(y1 == posicaoX)
					{
						(*mapa).setPacPortal(x1,y1);
						if((*mapa).getPosicao(posicaoX, posicaoY) == PORTAL)
							(*mapa).setPacPortal(x1,y1);
						else
							(*mapa).setVazio(posicaoX,posicaoY);
						posicaoX = x1;
						posicaoY = y1;
					}
					else
					{
						(*mapa).setPacPortal(x2,y2);
						if((*mapa).getPosicao(posicaoX, posicaoY) == PORTAL)
							(*mapa).setPacPortal(x2,y2);
						else
							(*mapa).setVazio(posicaoX,posicaoY);
						posicaoX = x2;
						posicaoY = y2;
					}
				}
			}

			else if(ultimoSentido == DIREITA)
			{
				evento((*mapa).getPosicao(posicaoX,posicaoY+1));
				if(((*mapa).getPosicao(posicaoX,posicaoY+1) != PAREDE) && (*mapa).getPosicao(posicaoX,posicaoY+1) != PORTAL)
				{
					if((*mapa).getPosicao(posicaoX, posicaoY) == PACPORTAL)
						(*mapa).setPortal(posicaoX, posicaoY);
					else
						(*mapa).setVazio(posicaoX,posicaoY);
					(*mapa).setPacman(posicaoX, posicaoY+1);
					posicaoY++;
				}
				else if((*mapa).getPosicao(posicaoX,posicaoY+1) == PORTAL)
				{
					int x1,x2,y1,y2;
					(*mapa).getPortais(&x1,&y1,&x2,&y2);

					if(y1 == posicaoX)
					{
						(*mapa).setPacPortal(x1,y1);
						if((*mapa).getPosicao(posicaoX, posicaoY) == PORTAL)
							(*mapa).setPacPortal(x1,y1);
						else
							(*mapa).setVazio(posicaoX,posicaoY);
						posicaoX = x1;
						posicaoY = y1;
					}
					else
					{
						(*mapa).setPacPortal(x2,y2);
						if((*mapa).getPosicao(posicaoX, posicaoY) == PORTAL)
							(*mapa).setPacPortal(x2,y2);
						else
							(*mapa).setVazio(posicaoX,posicaoY);
						posicaoX = x2;
						posicaoY = y2;
					}
				}

			}
		}
	}
}

void Pacman::evento(int valor)
{
	if(valor == 2)
	{
		pontuacao += 10;
	}
	if(valor == 3)
	{
		pontuacao += 50;
		estado = ZIKA;
		tempoDeForca = 20;
	}
	if(valor == 4)
	{
		//Void
	}

}