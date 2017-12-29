#include "fantasma.h"

Fantasma::Fantasma(int x, int y)
{
	this->posicaoX = x;
	this->posicaoY = y;
}
void Fantasma::mover(Ambiente* mapa)
{
	
	//Teste
	std::list<Aresta> arestas;
	std::list<Vertice> vertices;

	//Preenchendo a lista de vertices
	for(int i = 0; i < ALTURA; i++)
	{
		for(int j = 0; j < LARGURA; j++)
		{
			if((*mapa).getPosicao(i, j) != PAREDE  && (*mapa).getPosicao(i, j) != PORTAL)
			{
				Vertice novo(i,j);
				vertices.push_front(novo);
			}
		}
	}
	//Preenchendo a lista de arestas
	for(int i = 0; i < ALTURA; i++)
	{
		for(int j = 0; j < LARGURA; j++)
		{
			//Verificando os vizinhos
			if(i>0)
				if((*mapa).getPosicao(i-1, j) != PAREDE  || (*mapa).getPosicao(i-1, j) != PORTAL)
				{
					Vertice origem(i,j);
					Vertice destino(i-1,j);

					Aresta nova(origem, destino, 1);
					arestas.push_front(nova);
				}
			if(i<ALTURA-1)
				if((*mapa).getPosicao(i+1, j) != PAREDE  || (*mapa).getPosicao(i+1, j) != PORTAL)
				{
					Vertice origem(i,j);
					Vertice destino(i+1,j);

					Aresta nova(origem, destino, 1);
					arestas.push_front(nova);
				}
			if(j>0)
				if((*mapa).getPosicao(i, j-1) != PAREDE  || (*mapa).getPosicao(i, j-1) != PORTAL)
				{
					Vertice origem(i,j);
					Vertice destino(i,j-1);

					Aresta nova(origem, destino, 1);
					arestas.push_front(nova);
				}
			if(j<LARGURA-1)
				if((*mapa).getPosicao(i, j+1) != PAREDE  || (*mapa).getPosicao(i, j+1) != PORTAL)
				{
					Vertice origem(i,j);
					Vertice destino(i,j+1);

					Aresta nova(origem, destino, 1);
					arestas.push_front(nova);
				}
		}
	}

	//Para realizar o melhor movimento buscando o menor caminho a partir do ponto atual
	//Percorendo a lista de vertices em busca do vertice cujo a posicao é a do fantasma
	std::list<Vertice>::iterator k; 

	
	for ( k = vertices.begin(); k != vertices.end(); k++ )
    {
    	if(k->getX() == this->posicaoX && k->getY() == this->posicaoY)
    		break;
    }
   // cout << "Lista final ordenada...: X: " << k->getX() << " Y: " << k->getY() << endl;
    //Achado o fantasma na lista, definindo ele como origem
    //Vertice na posicao -1 -1 é o pai da origem
    Vertice pai(-1,-1);
    k->setDistanciaAcumulada(0);
    k->setPaiX(pai.getX());
    k->setPaiY(pai.getY());
    k->visitadoTrue();

    //printf("Coordenadas fantasma : x %d, y %d,\n",k->getX(), k->getY() );
    //printf("Valores pai: x %d , y %d \n", k->getPaiX(), k->getPaiY() );

    //printf("Coordenadas fantasma : x %d, y %d,\n",inicial->getX(), inicial->getY() );
    //printf("Valores pai: x %d , y %d \n", inicial->getPaiX(), inicial->getPaiY() );
    
    Vertice pacmanPosicao(17,6);

    //Achando a posição do pacman
    for(int i = 0; i < ALTURA; i++)
	{
		for(int j = 0; j < LARGURA; j++)
		{
			if((*mapa).getPosicao(i, j) == PACMAN || (*mapa).getPosicao(i, j) == PACPORTAL)
			{
				pacmanPosicao.setX(i);
				pacmanPosicao.setY(j);
			}
		}
	}

	printf("Coordenadas pacman: x %d, y %d \n", pacmanPosicao.getX(), pacmanPosicao.getY() );
    

    //Vai andar em todo mapa até achar o pacman
    while( ! (k->getY() == pacmanPosicao.getY() && k->getX() == pacmanPosicao.getX()) )
    {
    	printf("Entrei no while\n");
	    //Verificando todos os caminhos que se pode seguir a partir daqui
	    //Numerando todos os vertices adjacentes
	    std::list<Aresta>::iterator a;
	    for(a = arestas.begin(); a != arestas.end(); a++)
	    {
	    	//Nesse caso a aresta está saindo do nó analisado
	    	if((a->getOrigem())->getY() == k->getY() && (a->getOrigem())->getX() == k->getX() )
	    	{
	    		if((*mapa).getPosicao((a->getDestino())->getX(), (a->getDestino())->getY()) == PAREDE ||
	    		   (*mapa).getPosicao((a->getDestino())->getX(), (a->getDestino())->getY()) == PORTAL)
	    			continue;

			    std::list<Vertice>::iterator VerticeAtual; 

				for ( VerticeAtual = vertices.begin(); VerticeAtual != vertices.end(); VerticeAtual++ )
				{	    	
					if(!VerticeAtual->getVisitado())
					{
						if(VerticeAtual->getX() == (a->getDestino())->getX() && VerticeAtual->getY() == (a->getDestino())->getY() )
						{
							//printf("teste\n");
							break;
						}
					}

				}
    		//Verificando se a distancia acumulada nesse vertice é menor do que a nova distancia
	    		if(VerticeAtual->getDistanciaAcumulada() > k->getDistanciaAcumulada()+a->getPeso())
	    		{
	    			if(!VerticeAtual->getVisitado())
	    			{
	    				//Nesse caso posso alterar o destino
	    				VerticeAtual->setPaiX(k->getX());
	    				VerticeAtual->setPaiY(k->getY());
	    				VerticeAtual->setDistanciaAcumulada( k->getDistanciaAcumulada()+a->getPeso()  );
	    			}
	    		}
	    	}

	    }

	    k->visitadoTrue();
	    //Vizitando todos os vertices para obter o com menor distancia acumulada
		std::list<Vertice>::iterator u, menor; 

		menor = vertices.begin();	
		for ( u = vertices.begin(); u != vertices.end(); u++ )
		{
		    if(u->getDistanciaAcumulada() < menor->getDistanciaAcumulada() || menor->getVisitado())
		    	if(!u->getVisitado())
		    	{
		    		//printf("O menor é: %d em x e %d em y\n\n", u->getX(), u->getY());
		    		menor = u;
		    	}

		}
		//Agora irei visitar a casa de menor distancia acumulada
		k = menor;
	
		printf("\n\n\nCoordenadas Visitada : x %d, y %d,\n",k->getX(), k->getY() );

		if(k->getX() == pacmanPosicao.getX() && k->getY() == pacmanPosicao.getY())
			{
				printf("entrou\n");
				printf("enttrou\n");
			}
    	//printf("Valores pai da visitada: x %d , y %d \n\n\n\n", k->getPaiX(), k->getPaiY() );
	
	}

	printf("rola");
	std::list<Vertice>::iterator u;
	//Finalmente realizando a volta para realizar o movimento
	while(k->getPaiY() != this->posicaoY || k->getPaiX() != this->posicaoX)
	{
		

		 for ( u = vertices.begin(); u != vertices.end(); u++ )
		{
			if(u->getX() == k->getX() && u->getY() == k->getY())
			{
				k = u; 
			}
		}
	}



	if((*mapa).getPosicao(this->posicaoX, this->posicaoY) == COMIDAF)
	{
		(*mapa).setComida(this->posicaoX, this->posicaoY);
	}
	else
	{
		(*mapa).setVazio(this->posicaoX, this->posicaoY);
	}
	if((*mapa).getPosicao(u->getX(), u->getY()) == COMIDAP)
	{
		(*mapa).setFantasmaComida(u->getX(), u->getY());
	}
	else
	{
		(*mapa).setFantasma(u->getX(), u->getY());
	}
	this->posicaoX = u->getX();
	this->posicaoY = u->getY();
}