//Nesse arquivo está presente todos os cabeçalhos das funções presente no arquivo base.c
//Essas funções tem como objetivo ser a base de qualquer projeto, portanto havera funções como inicialização do SDL, e fechamento do mesmo.

#ifndef inicializacao_H
#define inicializacao_H

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <string>
#include <fstream>


#define PAREDE 1
#define COMIDAP 2
#define COMIDAG 3
#define VAZIO 4
#define PAREDEFANTASMA 5
#define PACMAN 6
#define PORTAL 7
#define PACPORTAL 8
#define FANTASMA 9
#define COMIDAF 10
#define COMIDAGF 11

#define ALTURA 31
#define LARGURA 28
//Fazendo algu qui num sei
using namespace std;
/***********************************************************************************/
//Algumas definições importantes
const string nome = "Pacman"; 
/***********************************************************************************/

//Inicio das funções

//Essa função inicializa todas a bibliotecas do SDL
int iniciar( SDL_Window** janela, SDL_Renderer** render);

#endif /* inicializacao_H */
