#include <psp2/kernel/processmgr.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

enum {
	SCREEN_WIDTH  = 960,
	SCREEN_HEIGHT = 544
};

int main(int argc, char *argv[]) 
{
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;

	if(SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO ) < 0) return 1;

	window = SDL_CreateWindow(
		"big songus", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN
	);
	if (window == NULL) return 1;

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL) return 1;

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) return 1;

	SDL_Texture* bigSongusImage = NULL;
	bigSongusImage = IMG_LoadTexture(renderer, "assets/BigSongus.png");

	SDL_Texture* bubsyImage = NULL;
	bubsyImage = IMG_LoadTexture(renderer, "assets/bubsy.jpg");
	
	SDL_Rect rectBubsy;
	rectBubsy.w = SCREEN_WIDTH;
	rectBubsy.h = SCREEN_HEIGHT;
	rectBubsy.x = 0;
	rectBubsy.y = 0;

	Mix_Music* music = NULL;
	music = Mix_LoadMUS("assets/sponge.ogg");

	Mix_PlayMusic(music, -1);

	unsigned int time;

	while (1) {
		SDL_Event e;
		if (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) break;
		}

		time = SDL_GetTicks();

		SDL_RenderClear(renderer);

		
		SDL_RenderCopy(renderer, bubsyImage, NULL, &rectBubsy);

		SDL_Rect rectSongus;
		rectSongus.w = SCREEN_HEIGHT * 0.75;
		rectSongus.h = SCREEN_HEIGHT * 0.75;
		rectSongus.x = ((sin(time * 0.005) + 1) * 0.5) * (SCREEN_WIDTH - rectSongus.w);
		rectSongus.y = ((cos(time * 0.005 * 3) + 1) * 0.5) * (SCREEN_HEIGHT - rectSongus.h);
		SDL_RenderCopy(renderer, bigSongusImage, NULL, &rectSongus);

		SDL_RenderPresent(renderer);
	}

	// SDL_SetRenderDrawColor( gRenderer, 255,0,0,255);
	// SDL_RenderFillRect( gRenderer, &fillRect );
	// SDL_RenderPresent( gRenderer );
	// SDL_Delay(4000);

	SDL_DestroyTexture(bigSongusImage);
	SDL_DestroyTexture(bubsyImage);

	Mix_FreeMusic(music);

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	
	SDL_Quit();
	sceKernelExitProcess(0);

	return 0;
}
