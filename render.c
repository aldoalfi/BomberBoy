 #include "header.h"

void Obstacles (GameState *gameState) {
		int i, j;

		// Calibrate border
		for (i=0; i<15; i++) {
			for (j=0; j<13; j++) {
				gameState->border[i][j]= (Border) {0, 0, 0, 0, 0};
			}
		}

		// Setup obstacles
		for (i=1; i<14; i++) {
			for (j=1; j<12; j++) {
				if (i%2 == 0) {
					if (j%2 != 0) {
						gameState->border[i][j].obj = rand()%2;
					}
				}
				else {
					gameState->border[i][j].obj = rand()%2;
				}
			}
		}

		// Setup game map border
		for (i=0; i<15; i++) {
			for (j=0; j<13; j++) {
				if (i==0 || i==14){
						gameState->border[i][j] = (Border) {i*50, j*50, 50, 50, 2};
				}
				else if (i%2 != 0) {
						if (j==0 || j==12) {
						gameState->border[i][j] = (Border) {i*50, j*50, 50, 50, 2};
					}
					else {
						if (gameState->border[i][j].obj == 1) {
							gameState->border[i][j] = (Border) {i*50, j*50, 50, 50, 1};
						}
					}
				}
				else {
						if (j%2 == 0) {
						gameState->border[i][j] = (Border) {i*50, j*50, 50, 50, 2};
					}
					else {
						if (gameState->border[i][j].obj == 1) {
							gameState->border[i][j] = (Border) {i*50, j*50, 50, 50, 1};
						}
					}
				}
			}
		}

	// Free border in respawn spot
	for (i=0; i<15; i++) {
		for (j=0; j<13; j++) {
			if ((i==1 && (j==1 || j==2 || j==10 || j==11)) || (i==2 && (j==1 || j==11)) || (i==12 && (j==1 || j==11)) || (i==13 && (j==1 || j==2 || j==10 || j==11))) {
				gameState->border[i][j]= (Border) {0, 0, 0, 0, 0};
			}
		}
	}
}

void loadSprites (GameState *gameState) {
	int i, j;

	SDL_Surface *surface= NULL;

	surface= IMG_Load("assets/map.png");
	gameState->map= SDL_CreateTextureFromSurface(gameState->renderer, surface);
	SDL_FreeSurface (surface);

	surface= IMG_Load("assets/char1.png");
	gameState->char1 = SDL_CreateTextureFromSurface(gameState->renderer, surface);
	SDL_FreeSurface(surface);

	surface= IMG_Load("assets/char2.png");
	gameState->char2 = SDL_CreateTextureFromSurface(gameState->renderer, surface);
	SDL_FreeSurface(surface);

	surface= IMG_Load("assets/bush.png");
	gameState->bush = SDL_CreateTextureFromSurface(gameState->renderer, surface);
	SDL_FreeSurface(surface);

	surface= IMG_Load("assets/game_menu.png");
	gameState->menu = SDL_CreateTextureFromSurface(gameState->renderer, surface);
	SDL_FreeSurface(surface);

	surface= IMG_Load("assets/pointer.png");
	gameState->arrow = SDL_CreateTextureFromSurface(gameState->renderer, surface);
	SDL_FreeSurface(surface);

	surface = IMG_Load("assets/bomb.png");
	gameState->bomb = SDL_CreateTextureFromSurface(gameState->renderer, surface);
	SDL_FreeSurface(surface);

  surface = IMG_Load("assets/boom1.png");
	gameState->boom1 = SDL_CreateTextureFromSurface(gameState->renderer, surface);
	SDL_FreeSurface(surface);

	surface = IMG_Load("assets/boom2.png");
	gameState->boom2 = SDL_CreateTextureFromSurface(gameState->renderer, surface);
	SDL_FreeSurface(surface);

  surface = IMG_Load("assets/p1win.png");
  gameState->playerwin[0] = SDL_CreateTextureFromSurface(gameState->renderer, surface);
  SDL_FreeSurface(surface);

  surface = IMG_Load("assets/p2win.png");
  gameState->playerwin[1] = SDL_CreateTextureFromSurface(gameState->renderer, surface);
  SDL_FreeSurface(surface);


	// Pointer spot
	gameState->pointer.x = 135;
	gameState->pointer.y = 330;

	// Player 1 respawn
	gameState->p1.x = 50;
	gameState->p1.y = 50;

	gameState->p1.dir = 1;
	gameState->p1.lookLeft = 0;
	gameState->p1.bomb = 0;
	gameState->p1.inBomb = 1;
  gameState->p1.inBomb2 = 1;

	// Player 2 respawn
	gameState->p2.x = 650;
	gameState->p2.y = 550;

	gameState->p2.dir = 1;
	gameState->p2.lookLeft = 0;
	gameState->p2.bomb = 0;
	gameState->p2.inBomb = 1;
  gameState->p2.inBomb2 = 1;

	Obstacles(gameState);
}

void Menu (GameState *gameState) {
	SDL_Renderer *renderer = gameState->renderer;

	// Draw Main Menu
	SDL_Rect menuRect = {0, 0, 750, 650};
	SDL_RenderCopy(renderer, gameState->menu, NULL, &menuRect);

	//Draw Pointer
	SDL_Rect pointRect = {gameState->pointer.x, gameState->pointer.y, 73, 32};
	SDL_RenderCopy(renderer, gameState->arrow, NULL, &pointRect);

	SDL_RenderPresent (renderer);
}

void Rendering (GameState *gameState) {

		int i, j;

		SDL_Renderer *renderer = gameState->renderer;

		// Draw Map
		SDL_Rect mapRect = {0, 0, 750, 650};
		SDL_RenderCopy(renderer, gameState->map, NULL, &mapRect);

		// Draw Obstacles
		for (i=1; i<14; i++) {
				for (j=1; j<12; j++) {
					if (gameState->border[i][j].obj == 1) {
							SDL_Rect bushRect = {gameState->border[i][j].x, gameState->border[i][j].y, 50, 50};
							SDL_RenderCopy(renderer, gameState->bush, NULL, &bushRect);
					} else if (gameState->border[i][j].obj == 0) {
					    gameState->border[i][j]= (Border) {0, 0, 0, 0, 0};
				    }
				}
		}

		// Draw Character 1
		SDL_Rect character1 = {gameState->p1.x, gameState->p1.y, 50, 50};
		SDL_Rect character12 = {40*(gameState->p1.dir), 0, 40, 58};

		if (gameState->p1.lookLeft == 1)
		{
			SDL_RenderCopyEx(renderer, gameState->char1, &character12, &character1, 0, NULL, SDL_FLIP_HORIZONTAL);
		}
		else {
			SDL_RenderCopyEx(renderer, gameState->char1, &character12, &character1, 0, NULL, SDL_FLIP_NONE);
		}

		// Draw Character 2
		SDL_Rect character2 = {gameState->p2.x, gameState->p2.y, 50, 50};
		SDL_Rect character22 = {40*(gameState->p2.dir), 0, 40, 58};

		if (gameState->p2.lookLeft == 1)
		{
			SDL_RenderCopyEx(renderer, gameState->char2, &character22, &character2, 0, NULL, SDL_FLIP_HORIZONTAL);
		}
		else {
			SDL_RenderCopyEx(renderer, gameState->char2, &character22, &character2, 0, NULL, SDL_FLIP_NONE);
		}

    // Draw Bomb jika ada
    if (gameState->p1.bomb == 1) {
		drawBomb(gameState, &gameState->b1, &gameState->p1);
	  }
	  if (gameState->p2.bomb == 1){
    	drawBomb(gameState, &gameState->b2, &gameState->p2);
	  }

	SDL_RenderPresent(renderer);
}

void drawBomb (GameState *gameState, Bomb *ptr, Player *ptr2) {
	int anim;
	int time = gameState->time;
	int timer = ptr->timer;
	SDL_Renderer *renderer = gameState->renderer;

	// Draw Bomb
	if (timer - time > 0) {
		if (timer - time > 150)
		{
		  anim = 0;
		} else if (timer - time < 150 && timer - time >= 120)
		{
		  anim = 1;
		} else if (timer - time < 120 && timer - time >= 90)
		{
		  anim = 2;
		} else if (timer - time < 90 && timer - time >= 60)
		{
		  anim = 3;
		} else if (timer - time < 60 && timer - time >= 30)
		{
		  anim = 4;
		} else if (timer - time < 30)
		{
		  anim = 5;
		}

		SDL_Rect bomb = {40*anim, 0, 40, 60};

		SDL_Rect bomb_spot = {ptr->x, ptr->y, 50, 50};

		SDL_RenderCopyEx(renderer, gameState->bomb, &bomb, &bomb_spot, 0, NULL, SDL_FLIP_NONE);
	}

	// Draw Fire + Fireball
	if (time > timer && time - timer < 30)
	{
		if (time - timer < 10)
		{
			anim = 0;
		} else if (time - timer > 10 && time - timer <= 20)
		{
			anim = 1;
		} else if (time - timer > 20)
		{
			anim = 2;
		}

		SDL_Rect bomb = {40*anim, 0, 40, 60};

		SDL_Rect bomb_spot = {ptr->x, ptr->y, 50, 50};

		SDL_Rect explosion = {40, 0, 40, 60};

		// Draw Fire
		int angle = 0, x = 0;
		Boom *head = NULL;

		if (time - timer < 20)
		{
			// Middle
			SDL_RenderCopyEx(renderer, gameState->boom2, &explosion, &bomb_spot, 0, NULL, SDL_FLIP_NONE);

			SDL_RenderCopyEx(renderer, gameState->boom2, &explosion, &bomb_spot, 90, NULL, SDL_FLIP_NONE);

			fireCollision_Wall(gameState, ptr, &head);

			// Others
			Boom *current = head;

			while (current != NULL)
			{
				if (current->value == 1) {
				  x = 0;
				}
				if (current->value == 2) {
				  x = 80;
				}
				if (current->value == 3) {
				  x = 0;
				  angle = 90;
				}
				if (current->value == 4) {
				  x = 80;
				  angle = 90;
				}

				SDL_Rect boom = {x, 0, 40, 60};

				SDL_Rect boom_spot =  {current->x, current->y, 50, 50};

				SDL_RenderCopyEx(renderer, gameState->boom2, &boom, &boom_spot, angle, NULL, SDL_FLIP_NONE);

				current = current->next;
			}
		}

		// Fireball
	    SDL_RenderCopyEx(renderer, gameState->boom1, &bomb, &bomb_spot, 0, NULL, SDL_FLIP_NONE);

	    clearList(&head);

	}

	// Bom Reset
	if (time - timer > 30) {
		ptr2->bomb = 0;
		ptr2->inBomb = 1;
		ptr2->inBomb2 = 1;
	}
}

void playerWin (GameState *gameState) {

  SDL_Renderer *renderer = gameState->renderer;

  if (gameState->status == 2) {
    // Draw Player 1 Win
    SDL_Rect playerRect = {0, 0, 750, 650};
    SDL_RenderCopy(renderer, gameState->playerwin[0], NULL, &playerRect);
    SDL_RenderPresent(renderer);
    SDL_Delay(3000);
  }
  else if (gameState->status == 3) {
    //Draw Player 2 Win
    SDL_Rect playerRect = {0, 0, 750, 650};
    SDL_RenderCopy(renderer, gameState->playerwin[1], NULL, &playerRect);
    SDL_RenderPresent(renderer);
    SDL_Delay(3000);
  }
}
