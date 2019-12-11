#include "header.h"

int main (int argc, char* argv[]) {

		GameState gameState;
		SDL_Window *window=NULL;
		SDL_Renderer *renderer=NULL;
		int done= 0, win= 0;

		gameState.time = 0;
		gameState.status = 0;

		SDL_Init(SDL_INIT_VIDEO); //Initialize SDL2

		window = SDL_CreateWindow ("BomberBoy",
									SDL_WINDOWPOS_UNDEFINED,
									SDL_WINDOWPOS_UNDEFINED,
									750,
									650,
									0
									);

		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

		gameState.renderer = renderer;

		loadSprites (&gameState);

		while(!done) {
				done= menuProcess(&gameState);
				Menu (&gameState);
		}

		SDL_DestroyTexture(gameState.menu);
		SDL_DestroyTexture(gameState.arrow);

		if (gameState.status == 1) {
			done= 0;
			while(!done) {
				done = eventProcess(&gameState);
				if (done == 1) {
					break;
				}

				// Collision for p1 and p2
				collisionDetect(&gameState, &gameState.p1);
				bombCollision(&gameState, &gameState.p1, &gameState.p2); // Collision p1, sama bomb p2 thd bomb p1
				collisionDetect(&gameState, &gameState.p2);
				bombCollision(&gameState, &gameState.p2, &gameState.p1);// Collision p2, sama bomb p1 thd bomb p2
				Rendering (&gameState);
				gameState.time++;

				if (fireCollision_Player(&gameState) != 0) {
					win = fireCollision_Player(&gameState);
					done = 1;
					if (win == 1) {
						gameState.status= 2;
					}
					else if (win == 2) {
						gameState.status= 3;
					}
				}
			}


			playerWin(&gameState);
		}

		if (gameState.status == 0) {
			return 0;
		}



		SDL_DestroyTexture(gameState.char1);
		SDL_DestroyTexture(gameState.char2);
		SDL_DestroyTexture(gameState.bomb);
		SDL_DestroyTexture(gameState.bush);
		SDL_DestroyTexture(gameState.boom1);
		SDL_DestroyTexture(gameState.boom2);
		SDL_DestroyTexture(gameState.map);
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_Quit();

		return main(1, "");
}
