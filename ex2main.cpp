#include <cstdlib>
#include <iostream>

#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"

#ifdef __cplusplus
extern "C"
#endif


int main(int argc, char **) {
	std::cout << "Begin main" << std::endl;

	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		system("PAUSE");
		return 1;
	}

	SDL_Window *win = SDL_CreateWindow("Hello World!", 50, 50, 640, 480, SDL_WINDOW_SHOWN);
	if (win == nullptr) {
		std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
		system("PAUSE");
		SDL_Quit();
		return 1;
	}

	SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	std::string imagePath = "../hello.bmp";
	SDL_Surface *bmp = SDL_LoadBMP(imagePath.c_str());
	if (bmp == 0) {
		SDL_DestroyWindow(win);
		SDL_DestroyRenderer(ren);
		std::cout << "SDL_LoadBMP Error: " << SDL_GetError() << std::endl;
		system("PAUSE");
		SDL_Quit();
		return 1;
	}

	SDL_Texture *tex = SDL_CreateTextureFromSurface(ren, bmp);
	SDL_FreeSurface(bmp);
	if (tex == 0) {
		SDL_DestroyWindow(win);
		SDL_DestroyRenderer(ren);
		std::cout << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
		system("PAUSE");
		SDL_Quit();
		return 1;
	}

	if (TTF_Init() == -1) {
		std::cout << "TTF_Init: " << TTF_GetError() << std::endl;
		system("PAUSE");
		exit(2);
	}

	TTF_Font *font;
	font = TTF_OpenFont("CharisSILR.ttf", 16);
	if (!font) {
		std::cout << "TTF_OpenFont: " << TTF_GetError() << std::endl;
		system("PAUSE");
	}

	//äëÿ íà÷àëà: 
	for (int i = 0; i < 5; i++) {
		SDL_RenderClear(ren);
		SDL_RenderCopy(ren, tex, nullptr, nullptr);
		SDL_RenderPresent(ren);
		SDL_Delay(1000);
	}


	SDL_Window *win2 = SDL_CreateWindow("Hello World!", 300, 500, 640, 480, SDL_WINDOW_SHOWN);
	if (win == 0) {
		std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
		system("PAUSE");
		SDL_Quit();
		return 1;
	}

	SDL_Renderer *ren2 = SDL_CreateRenderer(win2, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (win == 0) {
		SDL_DestroyWindow(win2);
		std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
		system("PAUSE");
		SDL_Quit();
		return 1;
	}

	bmp = SDL_LoadBMP(imagePath.c_str());
	if (bmp == nullptr) {
		SDL_DestroyWindow(win2);
		SDL_DestroyRenderer(ren2);
		std::cout << "SDL_LoadBMP Error: " << SDL_GetError() << std::endl;
		system("PAUSE");
		SDL_Quit();
		return 1;
	}

	SDL_Color color = {0, 0, 0};
	SDL_Surface *text_surface;
	if (!(text_surface = TTF_RenderUTF8_Solid(font, "ОТчислеено!", color))) {
		system("PAUSE");
		//handle error here, perhaps print TTF_GetError at least
	} else {
		SDL_BlitSurface(text_surface, nullptr, bmp, nullptr);
		//perhaps we can reuse it, but I assume not for simplicity.
		SDL_FreeSurface(text_surface);
	}

	SDL_Texture *tex2 = SDL_CreateTextureFromSurface(ren2, bmp);
	SDL_FreeSurface(bmp);
	if (tex2 == nullptr) {
		SDL_DestroyWindow(win2);
		SDL_DestroyRenderer(ren2);
		std::cout << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
		system("PAUSE");
		SDL_Quit();
		return 1;
	}


	SDL_Rect dst;
	SDL_Rect dst2;
	dst.x = 0;
	dst.y = 0;
	dst.w = 640;
	dst.h = 480;
	dst2.x = 0;
	dst2.y = 0;
	dst2.w = 640;
	dst2.h = 480;
	int i = 0, dirs = 1;
	int win1X = 0, win2X = 0, win1Y = 0, win2Y = 0;
	SDL_GetWindowPosition(win, &win1X, &win1Y);
	SDL_GetWindowPosition(win2, &win2X, &win2Y);
	//Our event structure
	SDL_Event e;
	bool quit = false;
	while (!quit) {
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				quit = true;
			}
			if (e.type == SDL_KEYDOWN) {
				quit = true;
			}
			if (e.type == SDL_MOUSEBUTTONDOWN && e.button.clicks == 2) {
				if ((e.button.button == SDL_BUTTON_LEFT && SDL_GetWindowFlags(win) & SDL_WINDOW_MOUSE_FOCUS) ||
				    (e.button.button == SDL_BUTTON_RIGHT && SDL_GetWindowFlags(win2) & SDL_WINDOW_MOUSE_FOCUS))
					quit = true;
			}
		}
		//Render the scene
		i += dirs;
		if (i > 10)
			dirs = -1;
		if (i < 0)
			dirs = +1;
		SDL_RenderClear(ren);
		dst.x = 10 * i;
		dst.y = 5 * i;
		SDL_RenderCopy(ren, tex, nullptr, &dst);
		SDL_RenderPresent(ren);
		SDL_RenderClear(ren2);
		dst2.x = -10 * i;
		dst2.y = -5 * i;
		SDL_RenderCopy(ren2, tex2, nullptr, &dst2);
		SDL_RenderPresent(ren2);
		int tmpX, tmpY;
		SDL_GetWindowPosition(win, &tmpX, &tmpY);
		if (tmpX != win1X && tmpY != win1Y)
			SDL_SetWindowPosition(win, win1X, win1Y);
		SDL_GetWindowPosition(win2, &tmpX, &tmpY);
		if (tmpX != win2X && tmpY != win2Y)
			SDL_SetWindowPosition(win2, win2X, win2Y);
	}

	TTF_Quit();

	SDL_DestroyTexture(tex);
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);

	std::cout << "End main before SDL_Quit" << std::endl;
	SDL_Quit();
	std::cout << "End main after SDL_Quit" << std::endl;
	system("PAUSE");
	return EXIT_SUCCESS;
} 