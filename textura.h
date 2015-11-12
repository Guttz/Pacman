#ifndef textura_H
#define textura_H

#include "inicializacao.h"

class Textura
{
	public:
		//Construtor
		Textura();

		//Destrutor
		~Textura();

		//Carrega uma imagem a partir de um caminho
		bool carregarArquivo( std::string caminho, SDL_Renderer* render);
		
		//Cria uma textura a partir de um texto
		bool carregarTexto( std::string texto, SDL_Color corTexto, SDL_Renderer* render, TTF_Font* fonte );

		//Desaloca uma textura
		void desalocaTextura();

		//Definir a cor à ser renderizada a textura
		void definirCor( Uint8 vermelho, Uint8 verde, Uint8 azul );

		//Define uma forma de renderizacao
		void setBlendMode( SDL_BlendMode blending );

		//Define a opacidade da textura
		void setAlpha( Uint8 alpha );
		
		//Imprime a textura na tela
		void renderizar( int x, int y,  SDL_Renderer* render, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, 
						SDL_RendererFlip flip = SDL_FLIP_NONE);

		//Gets image dimensions
		int getLargura();
		int getAltura();

	private:
		//The actual hardware texture
		SDL_Texture* textura;

		//Image dimensions
		int largura;
		int altura;
};		
#endif /* textura_H */