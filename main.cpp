#include "inicializacao.h"
#include "textura.h"
#include "mapa.h"
#include "pacman.h"
#include "fantasma.h"

#define MENU 0
#define JOGANDO 1
#define PAUSADO 2
#define FIMJOGO 3
#define HIGHSCORE 4

#define NOVO 1
#define PLACAR 2
#define SAIR 3

int main()
{
	inicio:
	//Instanciando as propriedades gerais do jogo
	SDL_Window* janela = NULL;
	SDL_Renderer* render = NULL; 
	Ambiente mapa;
	iniciar(&janela, &render);
	SDL_Event handle;
	bool quit = false;
	Pacman jogador(1,26);
	mapa.setPacman(1,26);
	Uint32 tempo, tempo2; 
	Fantasma fantasma(29,1);
	mapa.setFantasma(29,1);
	bool resetar = false;

	Fantasma fantasma2(1,1);
	mapa.setFantasma(1,1);

	int imprimindoContadora = 1;
	int imprimindoContadora2 = 0;

	//Variavel controle da maquina de estados
	int estado = MENU;

	//Variaveis para o menu
	Textura novoJogo, novoJogoFundo, titulo, tituloFundo, placar, placarFundo, sair, sairFundo, enfeite;
	SDL_Color cor = {255,255,0,255};
	SDL_Color corFundo = {0,0,0,255};
	SDL_Color corFundoSobre = { 255, 255, 255, 255};

	TTF_Font* font = TTF_OpenFont( "Fontes/font.ttf", 28 );
	TTF_Font* fontFundo = TTF_OpenFont( "Fontes/font.ttf", 29 );
	TTF_Font* fontTitulo = TTF_OpenFont( "Fontes/titulo.ttf", 48);
	TTF_Font* fontTituloFundo = TTF_OpenFont( "Fontes/titulo.ttf", 49);

	int sobre = 0;
	while(!quit)
	{
		switch(estado)
		{
			case MENU:
				novoJogo.carregarTexto("Novo jogo", cor, render, font);
				if(sobre == NOVO)
					novoJogoFundo.carregarTexto("Novo jogo", corFundoSobre, render, fontFundo);
				else
					novoJogoFundo.carregarTexto("Novo jogo", corFundo, render, fontFundo);


				placar.carregarTexto("Highscore", cor, render, font);
				if(sobre == PLACAR)
					placarFundo.carregarTexto("Highscore", corFundoSobre, render, fontFundo);
				else
					placarFundo.carregarTexto("Highscore", corFundo, render, fontFundo);

				sair.carregarTexto("Sair", cor, render, font);
				if(sobre == SAIR)
					sairFundo.carregarTexto("Sair", corFundoSobre, render, fontFundo);
				else
				sairFundo.carregarTexto("Sair", corFundo, render, fontFundo);

				titulo.carregarTexto("pacman", cor, render, fontTitulo);
				tituloFundo.carregarTexto("pacman", corFundo, render, fontTituloFundo);

				enfeite.carregarTexto("c22222222222222222222229", cor, render, fontTitulo);


				//Pegando as medidas da janela
				int largura, altura;
				SDL_GetWindowSize(janela, &largura, &altura);
				while( SDL_PollEvent( &handle ) != 0  )
			    {
			        if( handle.type == SDL_QUIT )
			        {
			            quit = true;
			            break;
			        }
			        else if(handle.type == SDL_MOUSEMOTION || handle.type == SDL_MOUSEBUTTONDOWN || handle.type == SDL_MOUSEBUTTONUP)
			        {
			        	int x, y;
        				SDL_GetMouseState( &x, &y );
        				//Verificando se o moouse esta sobre

        				//Novo jogo
        				if(y >= altura/2 && y<= (altura/2+ novoJogo.getAltura()))
        				{
        					if(x >= largura/2 -largura/8 && x<= (largura/2 -largura/8+ novoJogo.getLargura()))
        					{
        						sobre = NOVO;
        					}
        					else
	        				{
	        					sobre = 0;
	        				}
        				}
        				else if(y >= altura/2+ 2*novoJogo.getAltura() && y<= altura/2+ 2*novoJogo.getAltura()+placar.getAltura())
        				{
        					if(x >= largura/2 -largura/8 && x<= (largura/2 -largura/8+ novoJogo.getLargura()))
        					{
        						sobre = PLACAR;
        					}
        					else
	        				{
	        					sobre = 0;
	        				}
        				}
        				else if(y >= altura/2+ 4*novoJogo.getAltura() && y<= altura/2+ 4*novoJogo.getAltura()+placar.getAltura())
        				{
        					if(x >= largura/2 -largura/8 + novoJogo.getAltura()*3/2
        					 && x<= largura/2 -largura/8 + novoJogo.getAltura()*3/2 + sair.getLargura())
        					{
        						sobre = SAIR;
        					}
        					else
	        				{
	        					sobre = 0;
	        				}
        				}
        				else
        				{
        					sobre = 0;
        				}

        				if(handle.type == SDL_MOUSEBUTTONDOWN)
        				{
        					if(sobre == NOVO)
        					{
        						estado = JOGANDO;
        					}
        					else if(sobre == SAIR)
        					{
        						quit = true;
        					}
        					if(sobre == PLACAR)
        					{
        						estado = HIGHSCORE;
        					}
        				}
			        }
				}
				SDL_SetRenderDrawColor( render, 0, 0, 204, 0xFF );
				SDL_RenderClear( render );
				
				

				//Renderizando os textos na tela
				tituloFundo.renderizar(largura/2 -largura/5,altura/2 - altura/3, render);
				titulo.renderizar(largura/2 -largura/5,altura/2 - altura/3, render);

				enfeite.renderizar(largura/2 -largura/4,altura*0.3333, render);

				novoJogoFundo.renderizar( largura/2 -largura/8,altura/2, render);
				novoJogo.renderizar( largura/2 -largura/8,altura/2, render);

				placarFundo.renderizar( largura/2 -largura/8 ,altura/2 + 2*novoJogo.getAltura(), render);
				placar.renderizar( largura/2 -largura/8,altura/2+ 2*novoJogo.getAltura(), render);

				sairFundo.renderizar( largura/2 -largura/8 + novoJogo.getAltura()*3/2,altura/2 + 4*novoJogo.getAltura(), render);
				sair.renderizar( largura/2 -largura/8 + novoJogo.getAltura()*3/2,altura/2+ 4*novoJogo.getAltura(), render);
					
				SDL_RenderPresent(render);
			break;
			case JOGANDO:
				tempo = SDL_GetTicks(); 
				while( SDL_PollEvent( &handle ) != 0  )
		        {
					//User requests quit
		            if( handle.type == SDL_QUIT )
		            {
		                quit = true;
		                break;
		            }
		       	}
		       					fantasma.mover(&mapa);
		       
				jogador.mover(&mapa, &handle);
		       	if(fantasma.getX() == jogador.getX() && fantasma.getY() == jogador.getY())
				{
					estado = MENU;
					goto inicio;
				}
		       	if(imprimindoContadora2==0)
		       	{
		       		fantasma2.mover(&mapa);
		       		imprimindoContadora2++;
		       	}
		       	else
		       		imprimindoContadora2--;

				
				SDL_SetRenderDrawColor( render, 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear( render );
				//int tempo3 = SDL_GetTicks();
				mapa.imprime(&render);
				//cout<< SDL_GetTicks() - tempo3<<endl;
				SDL_RenderPresent(render);
				
				if(fantasma2.getX() == jogador.getX() && fantasma2.getY() == jogador.getY())
				{
					estado = MENU;
					goto inicio;
				}
				do{
					tempo2 = SDL_GetTicks();

					if(tempo2 - tempo > imprimindoContadora*250)
					{
					}
					}while(tempo2 - tempo <= 80);
					
					if(imprimindoContadora == 3)
						imprimindoContadora = 1;


			break;

		}
		
		
	}
	
	return 0;
}