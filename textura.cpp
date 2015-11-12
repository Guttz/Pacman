#include "textura.h"

Textura::Textura()
{
	textura = NULL;
	largura = 0;
	altura  = 0;
}
Textura::~Textura()
{
	desalocaTextura();
}
bool Textura::carregarArquivo( std::string caminho, SDL_Renderer* render)
{
	desalocaTextura();

	//Criando uma variavel que será o resultado do metodo
	SDL_Texture* novaTextura = NULL;

	//Carregando a imagem para uma surface auxiliar
	SDL_Surface* imagemCarregada = IMG_Load( caminho.c_str() );
	if( imagemCarregada == NULL )
    {
       	printf( "En: Unable to load image! SDL_image Error: %s\n", IMG_GetError() );
       	printf( "Pt: Não foi possivel carregar a imagem! Erro: %s\n", IMG_GetError() );
	}
	else
	{
		//Color key image
		SDL_SetColorKey( imagemCarregada, SDL_TRUE, SDL_MapRGB( imagemCarregada->format, 255, 0, 255 ));

		//Create texture from surface pixels
        novaTextura = SDL_CreateTextureFromSurface( render, imagemCarregada );
		if( novaTextura == NULL )
		{
			printf( "Unable to create texture from %s! SDL Error: %s\n", caminho.c_str(), SDL_GetError() );
		}
		else
		{
			//Get image dimensions
			largura = imagemCarregada->w;
			altura = imagemCarregada->h;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface( imagemCarregada );
	}

	//Return success
	textura = novaTextura;
	return textura != NULL;
}

bool Textura::carregarTexto( std::string texto, SDL_Color corTexto, SDL_Renderer* render, TTF_Font* fonte )
{
	//Deleta textura anterior
	desalocaTextura();

	//Renderiza textura de texto
	SDL_Surface* surfaceTexto = TTF_RenderText_Solid( fonte, texto.c_str(), corTexto );
	if( surfaceTexto == NULL )
	{
		printf( "En: Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
       	printf( "Pt: Não foi possivel criar a render apartir de um texto! Erro: %s\n", TTF_GetError() );
    }
    else
    {
		//Criar textura a partir dos pixels da surface
        textura = SDL_CreateTextureFromSurface( render, surfaceTexto );
		if( textura == NULL )
		{
			printf( "En: Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
		    printf( "Pt: Não foi possivel criar a textura apartir de um texto! Erro: %s\n", SDL_GetError() );
		}
		else
		{
			//Armazenando as dimensões da surface
			largura = surfaceTexto->w;
			altura = surfaceTexto->h;
		}

		//Deleta a surface
		SDL_FreeSurface( surfaceTexto );
	}

	//Retorna sucesso
	return textura != NULL;
}

void Textura::desalocaTextura()
{
	//Deleta textura se existir
	if( textura != NULL )
	{
		SDL_DestroyTexture( textura );
		textura = NULL;
		largura = 0;
		altura = 0;
	}
}

void Textura::definirCor( Uint8 vermelho, Uint8 verde, Uint8 azul )
{
	//Modula a textura em rbg
	SDL_SetTextureColorMod( textura, vermelho, verde, azul );
}

void Textura::setBlendMode( SDL_BlendMode blending )
{
	//Seta o blending da textura
	SDL_SetTextureBlendMode( textura, blending );
}
		
void Textura::setAlpha( Uint8 alpha )
{
	//Modula o alpha na textura
	SDL_SetTextureAlphaMod( textura, alpha );
}

void Textura::renderizar( int x, int y, SDL_Renderer* render, SDL_Rect* dimensoes, double angulo, SDL_Point* centro,
 	SDL_RendererFlip girar)
{
	//Quadrante que ajusta na tela onde vai ser renderizado
	SDL_Rect quadranteRenderizado = { x, y, largura, altura };

	//Ajusta o quadrante as dimensoes desejadas
	if( dimensoes != NULL )
	{
		quadranteRenderizado.w = dimensoes->w;
		quadranteRenderizado.h = dimensoes->h;
	}

	//Imprime na tela
	SDL_RenderCopyEx( render, textura, dimensoes, &quadranteRenderizado, angulo, centro, girar );
}

int Textura::getLargura()
{
	return largura;
}

int Textura::getAltura()
{
	return altura;
}
