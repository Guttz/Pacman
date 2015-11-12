#include "inicializacao.h"

int iniciar( SDL_Window** janela, SDL_Renderer** render)
{
	bool sucesso = true;
	

	//Inicia o SDL
	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		printf("En: SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
		printf("Pt: SDL nao pode ser iniciado! Err	o: %s\n", SDL_GetError() );
		sucesso = false;
	}     
	else
	{
		//Adquirindo as medidas da tela
		//Variavel que armazena as medidas da tela e a frequencia
		SDL_DisplayMode telaAtual;
		
		//Chamando a função para definir as propriedades da tela atual (retorna 0 se for sucesso)
		if(SDL_GetCurrentDisplayMode(0, &telaAtual) != 0)
		{
			//Em caso de erro
			printf("En: Could not get display mode for video display : %s",  SDL_GetError());
			printf("Pt: Nao foi possivel obter um monitor e suas propriedades  : %s", SDL_GetError());	
			sucesso = false;
		}
		else
		{
			int alturaTela =28*telaAtual.h/34;
			int larguraTela = 31*telaAtual.h/34;

			ofstream out;
			out.open("config.txt");
			out<<"altura = "<< alturaTela <<"\n"<<"largura = "<< larguraTela;
			
			//out<<"altura = "<<395<<"\n"<<"largura = "<< 487;
			out.close();

			*janela = SDL_CreateWindow( nome.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, larguraTela , alturaTela, SDL_WINDOW_SHOWN );
			//*janela = SDL_CreateWindow( nome.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 487, 395, SDL_WINDOW_SHOWN );

			if(*janela == NULL)
			{
				printf( "En: Window could not be created! SDL_Error: %s\n", SDL_GetError() );
				printf( "Pt: Não foi possivel criar a janela! Erro: %s\n", SDL_GetError() );
				sucesso = false;
			}
			else
			{
				*render = SDL_CreateRenderer( *janela, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
				//Verificando se render foi inicializada com sucesso
				if(*render == NULL)
				{
					printf( "En: Render could not be created! SDL Error: %s\n", SDL_GetError() );
					printf( "Pt: Não foi possivel criar a Renderer! Erro: %s\n", SDL_GetError() );
					sucesso = false	;
				}
				else
				{
						//Se a render tiver sido iniciada corretamente, definir a cor dela
						SDL_SetRenderDrawColor( *render, 0xFF, 0xFF, 0xFF, 0xFF );

						//Inicializando a biblioteca do SDL para carregar imagens .png
						int imgFlags = IMG_INIT_PNG;
						if( !( IMG_Init( imgFlags ) & imgFlags ) )
						{
							printf( "En: SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
							printf( "Pt: Não foi possivel iniciar a biblioteca SDL_image! Erro: %s\n", IMG_GetError() );
							sucesso = false;
						}
						//Inicado as bibliotecas basicas do SDL vamos inicar duas outra bibliotecas, uma de controle de som e outra de fontes
						if(TTF_Init() == -1)
						{
							printf("En: SDL_ttf could not initialize! SDL_tff Error: %s\n", TTF_GetError() );
							printf("Pt: Não foi possivel iniciar a biblioteca SDL_ttf ! SDL_tff Erro: %s\n", TTF_GetError() );
							sucesso = false;
						}

						//Iniciando a biblioteca SDL_mixer
						if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
						{
						    printf( "En: SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
						    printf( "Pt: Não foi possivel iniciar a biblioteca SDL_mixer! Erro: %s\n", Mix_GetError() );
						    sucesso = false;
						}
				}

				

			}
		}
		

		
	}
	return sucesso;
}
