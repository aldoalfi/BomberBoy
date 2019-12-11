#ifndef DEFINE_H
	#define DEFINE_H

	#include <SDL2/SDL.h>
	#include <SDL2/SDL_image.h>

	#include <stdio.h>
	#include <stdlib.h>
	#include <conio.h>

	typedef struct {
		int x, y, w, h, obj; // obj--> 0 = Path, 1 = Obstacle, 2 = Wall
	} Border;

	struct Boom {
	int value;
	int x, y;
	struct Boom *next;
	};
	typedef struct Boom Boom;

	typedef struct {
		int x, y;
		int timer;
	} Bomb;

	typedef struct {
		Bomb b1;

		int x, y;
		int dir;
		int lookLeft;
		int bomb;

		int inBomb; // Dalem bomb sendiri atau ngga
		int inBomb2; // Dalem bomb musuh atau ngga
	} Player;

	typedef struct {
	  Border border[15][13];
	  Player p1;
		Player p2;
		Bomb b1;
		Bomb b2;
		Player pointer;

	  SDL_Texture *map;
	  SDL_Texture *char1;
		SDL_Texture *char2;
		SDL_Texture *bush;
		SDL_Texture *menu;
		SDL_Texture *arrow;
		SDL_Texture *bomb;
	  SDL_Texture *boom1;
	  SDL_Texture *boom2;
		SDL_Texture *playerwin[2];
	  SDL_Renderer *renderer;

		int time;
		int status;
	} GameState;

	#define SPEED 5
	#define FRAME_TIME 6

	//  Process Functions
	int eventProcess (GameState *gameState);

	int menuProcess (GameState *gameState);

	void collisionDetect (GameState *gameState, Player *ptr);

	void bombCollision(GameState *gameState, Player *ptr, Player *ptr2);

	void fireCollision_Wall (GameState *gameState, Bomb *ptr, Boom** head);

	int fireCollision_Player (GameState *gameState);

	// Render Functions
	void loadSprites (GameState *gameState);

	void Rendering (GameState *gameState);

	void drawBomb (GameState *gameState, Bomb *ptr, Player *ptr2);

	void Menu (GameState *gameState);

	void playerWin (GameState *gameState);

	// Linked List Functions
	void newBoom(int value, int x, int y, Boom** head);

	void clearList (Boom** head);


#endif
