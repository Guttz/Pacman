#include "inicializacao.h"
#include "textura.h"
#include "mapa.h"
#include "pacman.h"
#include "fantasma.h"

#define MENU 0
#define JOGANDO 1
#define PAUSADO 2
#define FIMJOGO 3

int main()
{
	SDL_Window* janela = NULL;	
	SDL_Renderer* render = NULL; 
	Ambiente mapa;

	iniciar(&janela, &render);
	SDL_Event handle;
	bool quit = false;
	Pacman jogador(1,26);
	mapa.setPacman(1,26);
	Fantasma fantasma(29,1);
	mapa.setFantasma(29,1);
	Uint32 tempo, tempo2;
	int imprimindoContadora = 1;


	Mix_PlayChannel( -1, Mix_LoadWAV( "Sons/introducao.wav" ), 0 );
		
	while(!quit)
	{
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
		SDL_SetRenderDrawColor( render, 0xFF, 0xFF, 0xFF, 0xFF );
		SDL_RenderClear( render );
		//int tempo3 = SDL_GetTicks();
		mapa.imprime(&render);
		//cout<< SDL_GetTicks() - tempo3<<endl;
		SDL_RenderPresent(render);

		do{
			tempo2 = SDL_GetTicks();

			if(tempo2 - tempo > imprimindoContadora*250)
			{
			}
			}while(tempo2 - tempo <= 80);
			
			if(imprimindoContadora == 3)
				imprimindoContadora = 1;		
	}
	
	return 0;
}





/*if(iniciar(&janela, &render) )
	{
		int estado = MENU;
		switch(estado)
		{
			case MENU:
				//menu
			break;
			case JOGANDO:
				//jogando
			break;
			case PAUSADO:
				//PAUSADO	
			break;
			case FIMJOGO:
				//fim jogo
			break;


		}
	}*/


		/*{SDL_Color cor = {0,122,122,255};
		TTF_Font* font = TTF_OpenFont( "Fontes/font.ttf", 28 );

		Textura textura;

		textura.carregarTexto( "Rola rola rola", cor, render, font );
		SDL_Event handle;
		bool quit = false;
		while(!quit)
		{
			while( SDL_PollEvent( &handle ) != 0 )
                {
			//User requests quit
                    if( handle.type == SDL_QUIT )
                    {
                        quit = true;
                    }
		SDL_SetRenderDrawColor( render, 0xFF, 0xFF, 0xFF, 0xFF );
        SDL_RenderClear( render );
		textura.renderizar( 10,10, render);
		SDL_RenderPresent(render);
	}
		}}*/