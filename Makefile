OBJS = main.cpp inicializacao.cpp textura.cpp mapa.cpp pacman.cpp

CC = g++

LDFLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -std=c++11

OBJ_NAME = inicializou

all: $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o $(OBJ_NAME)
