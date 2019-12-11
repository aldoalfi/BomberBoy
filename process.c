#include "header.h"

int menuProcess(GameState *gameState) {

	SDL_Event event;

	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_KEYUP) {
			switch (event.key.keysym.sym) {
				case SDLK_DOWN:
					if (gameState->pointer.y == 330) {
						gameState->pointer.y = 395;
					}
					else {
						gameState->pointer.y = 330;
					}
				break;
				case SDLK_UP:
				if (gameState->pointer.y == 330) {
					gameState->pointer.y = 395;
				}
				else {
					gameState->pointer.y = 330;
				}
				break;
				case SDLK_RETURN:
				case SDLK_SPACE:
					if (gameState->pointer.y == 330) {
						gameState->status = 1;
					}
					else if (gameState->pointer.y == 395) {
						gameState->status = 0;
					}

					return 1;
				break;
			}
		}

	return 0;
	}
}

int eventProcess(GameState *gameState) {

	int frame = gameState->time;

	SDL_Event event;

	const Uint8 *key = SDL_GetKeyboardState(NULL);

	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			return 1;
		}
	}

	// Player 1 move
	if (key[SDL_SCANCODE_W])
	{
		gameState->p1.y -= SPEED;
		if (frame % FRAME_TIME == 0) {
			gameState->p1.dir -= 1;
			if (gameState->p1.dir < 0) {
				gameState->p1.dir = 9;
			} else if (gameState->p1.dir < 8) {
				gameState->p1.dir = 0;
			}
		}
	}

	else if (key[SDL_SCANCODE_S])
	{
		gameState->p1.y += SPEED;
		if (frame % FRAME_TIME == 0) {
			gameState->p1.dir += 1;
			if (gameState->p1.dir < 1 || gameState->p1.dir > 3) {
				gameState->p1.dir = 1;
			}
		}
	}

	else if (key[SDL_SCANCODE_A])
	{
		gameState->p1.x -= SPEED;
		gameState->p1.lookLeft = 1;
		if (frame % FRAME_TIME == 0) {
			gameState->p1.dir += 1;
			if (gameState->p1.dir < 4 || gameState->p1.dir > 7) {
				gameState->p1.dir = 4;
			}
		}
	}

	else if (key[SDL_SCANCODE_D]) {
		gameState->p1.x += SPEED;
		gameState->p1.lookLeft = 0;
		if (frame % FRAME_TIME == 0) {
			gameState->p1.dir += 1;
			if (gameState->p1.dir < 4 || gameState->p1.dir > 7) {
				gameState->p1.dir = 4;
			}
		}
	}

	// Player 2 move
	if (key[SDL_SCANCODE_UP])
	{
		gameState->p2.y -= SPEED;
		if (frame % FRAME_TIME == 0) {
			gameState->p2.dir -= 1;
			if (gameState->p2.dir < 0) {
				gameState->p2.dir = 9;
			} else if (gameState->p2.dir < 8) {
				gameState->p2.dir = 0;
			}
		}
	}

	else if (key[SDL_SCANCODE_DOWN])
	{
		gameState->p2.y += SPEED;
		if (frame % FRAME_TIME == 0) {
			gameState->p2.dir += 1;
			if (gameState->p2.dir < 1 || gameState->p2.dir > 3) {
				gameState->p2.dir = 1;
			}
		}
	}

	else if (key[SDL_SCANCODE_LEFT])
	{
		gameState->p2.x -= SPEED;
		gameState->p2.lookLeft = 1;
		if (frame % FRAME_TIME == 0) {
			gameState->p2.dir += 1;
			if (gameState->p2.dir < 4 || gameState->p2.dir > 7) {
				gameState->p2.dir = 4;
			}
		}
	}

	else if (key[SDL_SCANCODE_RIGHT]) {
		gameState->p2.x += SPEED;
		gameState->p2.lookLeft = 0;
		if (frame % FRAME_TIME == 0) {
			gameState->p2.dir += 1;
			if (gameState->p2.dir < 4 || gameState->p2.dir > 7) {
				gameState->p2.dir = 4;
			}
		}
	}


	// Process Bomb Key (1)
	if (key[SDL_SCANCODE_SPACE] && gameState->p1.bomb == 0) {

		int x = gameState->p1.x, y = gameState->p1.y;

		// Biar pas di kotak
		while (x % 50 != 0) {
			x -= 1;
		}
		while (y % 50 != 0) {
			y -= 1;
		}

		gameState->b1.x = x;
		gameState->b1.y = y;
		gameState->b1.timer = gameState->time + 180;
		gameState->p1.bomb = 1;
	}

	// Process Bomb Key (2)
	if (key[SDL_SCANCODE_RETURN] && gameState->p2.bomb == 0) {

		int x = gameState->p2.x, y = gameState->p2.y;

		// Biar pas di kotak
		while (x % 50 != 0) {
			x -= 1;
		}
		while (y % 50 != 0) {
			y -= 1;
		}

		gameState->b2.x = x;
		gameState->b2.y = y;
		gameState->b2.timer = gameState->time + 180;
		gameState->p2.bomb = 1;
	}
	return 0;
}

void collisionDetect(GameState *gameState, Player *ptr) {

	int i, j;

  //Check for collision with any border
	for (i=0; i<15; i++) {
		for (j=0; j<13; j++) {

			int Ax = ptr->x, Ay = ptr->y;
			int Ax_Max = ptr->x + 49;
			int Ay_Max = ptr->y + 49;

			int Bx = gameState->border[i][j].x, By = gameState->border[i][j].y;
			int Bx_Max = gameState->border[i][j].w + Bx;
			int By_Max = gameState->border[i][j].h + By;

			if(Ay_Max> By && Ay<By_Max)
			{
				//LEFT collision
				if(Ax < Bx_Max && Ax_Max > Bx_Max)
				{
					//correct x
					ptr->x = Bx_Max;
					ptr->y = Ay;
				}

				//RIGHT collision
				else if(Ax_Max > Bx && Ax < Bx)
				{
					//correct x
					ptr->x = Bx-50;
					ptr->y = Ay;
				}
			}

			if(Ax < Bx_Max && Ax_Max > Bx)
			{
				//UP collision
				if(Ay < By_Max && Ay_Max > By_Max)
				{
					//correct y
					ptr->y = By_Max;

					if ((Bx_Max - Ax) < 30 && (Ax - Bx) < 50) {
						ptr->x = Ax + 1;
					} else if ((Ax_Max - Bx) < 30 && (Bx_Max - Ax_Max) < 50) {
						ptr->x = Ax - 1;
					} else {
						ptr->x = Ax;
					}
				}

				//DOWN collision
				else if(Ay_Max > By && Ay < By)
				{
					//correct y
					ptr->y = By-50;

					if ((Bx_Max - Ax) < 30 && (Ax - Bx) < 50) {
						ptr->x = Ax + 1;
					} else if ((Ax_Max - Bx) < 30 && (Bx_Max - Ax_Max) < 50) {
						ptr->x = Ax - 1;
					} else {
						ptr->x = Ax;
					}
				}
			}
		}
	}

}

void bombCollision(GameState *gameState, Player *ptr, Player *ptr2) {

	int Ax = ptr->x, Ay = ptr->y;
	int Ax_Max = ptr->x + 49;
	int Ay_Max = ptr->y + 49;

	int Bx, By, Bx2, By2;

	if (Ax == gameState->p1.x) { // Collision p1
		Bx = gameState->b1.x;
		By = gameState->b1.y;
		Bx2 = gameState->b2.x;
		By2 = gameState->b2.y;
	} else { // Collision p2
		Bx = gameState->b2.x;
		By = gameState->b2.y;
		Bx2 = gameState->b1.x;
		By2 = gameState->b1.y;
	}

	int Bx_Max = Bx + 49;
	int By_Max = By + 49;
	int Bx_Max2 = Bx2 + 49;
	int By_Max2 = By2 + 49;

	if (ptr->bomb == 1)
	{
		if (Ay_Max > By && Ay < By_Max) { // Jika bom disamping char

			// Cek dulu, character ada di bom atau gak
			if (ptr->inBomb == 1)
			{
				if (Ax >= Bx && Ax <= Bx_Max) {
					ptr->inBomb = 1;
				} else if (Ax_Max >= Bx && Ax_Max <= Bx_Max) {
					ptr->inBomb = 1;
				} else {
					ptr->inBomb = 0;
				}

			} else { // Kalo char udah gak pas di bom, lakuin collision detection
				if (Ax < Bx_Max && Ax_Max > Bx_Max)
				{
					ptr->x = Bx_Max;
					ptr->y = By;

				} else if (Ax_Max > Bx && Ax < Bx) {
					ptr->x = Bx - 50;
					ptr->y = By;
				}
			}
		}

		if(Ax < Bx_Max && Ax_Max > Bx) // Jika bom diletakkan secara vertikal
		{
			// Cek char pas di bom atau gak
			if (ptr->inBomb == 1)
			{
				if (Ay >= By && Ay <= By_Max) {
					ptr->inBomb = 1;

				} else if (Ay_Max >= By && Ay_Max <= By_Max) {
					ptr->inBomb = 1;

				} else {
					ptr->inBomb = 0;
				}

			} else {
				if(Ay < By_Max && Ay_Max > By_Max)
				{
					ptr->y= By_Max;
					ptr->x = Bx;

				} else if(Ay_Max > By && Ay < By) {
					ptr->y = By - 50;
					ptr->x = Bx;
				}
			}
		}
	}

	if (ptr2->bomb == 1)
	{
		if (Ay_Max > By2 && Ay < By_Max2) { // Jika bom disamping char

			// Cek dulu, character ada di bom atau gak
			if (ptr->inBomb2 == 1)
			{
				if (Ax >= Bx2 && Ax <= Bx_Max2) {
					ptr->inBomb2 = 1;
				} else if (Ax_Max >= Bx2 && Ax_Max <= Bx_Max2) {
					ptr->inBomb2 = 1;
				} else {
					ptr->inBomb2 = 0;
				}

			} else { // Kalo char udah gak pas di bom, lakuin collision detection
				if (Ax < Bx_Max2 && Ax_Max > Bx_Max2)
				{
					ptr->x = Bx_Max2;
					ptr->y = By2;

				} else if (Ax_Max > Bx2 && Ax < Bx2) {
					ptr->x = Bx2 - 50;
					ptr->y = By2;
				}
			}
		}

		if(Ax < Bx_Max2 && Ax_Max > Bx2) // Jika bom diletakkan secara vertikal
		{
			// Cek char pas di bom atau gak
			if (ptr->inBomb2 == 1)
			{
				if (Ay >= By2 && Ay <= By_Max2) {
					ptr->inBomb2 = 1;

				} else if (Ay_Max >= By2 && Ay_Max <= By_Max2) {
					ptr->inBomb2 = 1;

				} else {
					ptr->inBomb2 = 0;
				}

			} else {
				if(Ay < By_Max2 && Ay_Max > By_Max2)
				{
					ptr->y= By_Max2;
					ptr->x = Bx2;

				} else if(Ay_Max > By2 && Ay < By2) {
					ptr->y = By2 - 50;
					ptr->x = Bx2;
				}
			}
		}
	}
}

void fireCollision_Wall (GameState *gameState, Bomb *ptr, Boom** head) {
	int Bx = ptr->x, By = ptr->y;
	int i, j;
	int left = 1, right = 1, up = 1, down = 1;

	for (i = 0; i < 15; i++) {
		for (j = 0; j < 13; j++) {

			int Bor_x = gameState->border[i][j].x, Bor_y = gameState->border[i][j].y;

			if (gameState->border[i][j].obj != 0) {
				if (Bor_x == Bx - 50 && By == Bor_y) {
					left = 0;
					if (gameState->border[i][j].obj == 1) {
						gameState->border[i][j].obj = 0;
					}
				}
				if (Bor_x == Bx + 50 && Bor_y == By) {
					right = 0;
					if (gameState->border[i][j].obj == 1) {
						gameState->border[i][j].obj = 0;
					}
				}
				if (Bor_y == By - 50 && Bx == Bor_x) {
					up = 0;
					if (gameState->border[i][j].obj == 1) {
						gameState->border[i][j].obj = 0;
					}
				}
				if (Bor_y == By + 50 && Bx == Bor_x) {
					down = 0;
					if (gameState->border[i][j].obj == 1) {
						gameState->border[i][j].obj = 0;
					}
				}
			}
		}
	}

	if (left == 1) {
		newBoom(1, Bx-50, By, &*head);
	}
	if (right == 1) {
		newBoom(2, Bx+50, By, &*head);
	}
	if (up == 1) {
		newBoom(3, Bx, By-50, &*head);
	}
	if (down == 1) {
		newBoom(4, Bx, By+50, &*head);
	}
}

int fireCollision_Player (GameState *gameState) {

	// Koordinat semua
	int Ax = gameState->p1.x, Ay = gameState->p1.y;
	int Ax2 = gameState->p2.x, Ay2 = gameState->p2.y;

	int Bx = gameState->b1.x, By = gameState->b1.y;
	int Bx2 = gameState->b2.x, By2 = gameState->b2.y;

	int time = gameState->time;
	int timer = gameState->b1.timer;

	// Bomb nya p1
	if (gameState->p1.bomb) {
		if (time > timer && time - timer < 30) {
			// Kena p1 (bundir)
			if (Ax <= Bx - 50 && By == Ay) {
				return 2;
			}
			else if (Ax <= Bx + 50 && By == Ay) {
				return 2;
			}
			else if (Ay <= By - 50 && Bx == Ax) {
				return 2;
			}
			else if (Ay <= By + 50 && Bx == Ax) {
				return 2;
			}
			// Kena p2
			if (Ax2 <= Bx - 50 && By == Ay2) {
				return 1;
			}
			else if (Ax2 <= Bx + 50 && By == Ay2) {
				return 1;
			}
			else if (Ay2 <= By - 50 && Bx == Ax2) {
				return 1;
			}
			else if (Ay2 <= By + 50 && Bx == Ax2) {
				return 1;
			}
		}
	}

	// Bomb nya p2
	timer = gameState->b2.timer;
	if (gameState->p2.bomb) {
		if (time > timer && time - timer < 30) {
			// Kena p1
			if (Ax <= Bx2 - 50 && By2 == Ay) {
				return 2;
			}
			else if (Ax <= Bx2 + 50 && By2 == Ay) {
				return 2;
			}
			else if (Ay <= By2 - 50 && Bx2 == Ax) {
				return 2;
			}
			else if (Ay <= By2 + 50 && Bx2 == Ax) {
				return 2;
			}
			// Kena p2 (bundir)
			if (Ax2 <= Bx2 - 50 && By2 == Ay2) {
				return 1;
			}
			else if (Ax2 <= Bx2 + 50 && By2 == Ay2) {
				return 1;
			}
			else if (Ay2 <= By2 - 50 && Bx2 == Ax2) {
				return 1;
			}
			else if (Ay2 <= By2 + 50 && Bx2 == Ax2) {
				return 1;
			}
		}
	}

	return 0;
}

void newBoom (int value, int x, int y, Boom** head) {
	Boom *link = (Boom*)malloc(sizeof(Boom));
	Boom *current = NULL;

	link->value = value;
	link->x = x;
	link->y = y;
	link->next = NULL;

	if (*head == NULL)
	{
		*head = link;
		return;
	}

	current = *head;

	while(current->next != NULL)
	{
		current = current->next;
	}

	current->next = link;
}

void clearList (Boom** head) {
	Boom *current = *head;
	Boom *next;

	while (current != NULL)
	{
    	next = current->next;
		free(current);
    	current = next;
	}

	*head = NULL;
}
