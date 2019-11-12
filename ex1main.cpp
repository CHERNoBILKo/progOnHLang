#include <SDL2/SDL.h>
#include <cstdlib>
#include <iostream>

#ifdef __cplusplus
extern "C"
#endif
int main(int argc, char**){
	std::cout<<"Begin main"<< std::endl;

	if(SDL_Init(SDL_INIT_VIDEO)!=0){
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		system("PAUSE");
		return 1;
	}
	SDL_DisplayMode DM;
	SDL_GetCurrentDisplayMode(0, &DM);
	auto Width = DM.w;
	auto Height = DM.h;

	SDL_Window *win1 = SDL_CreateWindow("Window 1", 0, 0, 640, 480, SDL_WINDOW_SHOWN);
	SDL_Window *win2 = SDL_CreateWindow("Window 2", Width-640,Height,640,480, SDL_WINDOW_SHOWN);
	if(win1 == nullptr){
		std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
		system("PAUSE");
		SDL_Quit();
		return 1;
	}
	if(win2 == nullptr){
		std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
		system("PAUSE");
		SDL_Quit();
		return 1;
	}

	SDL_Renderer *ren1 = SDL_CreateRenderer(win1, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	SDL_Renderer *ren2 = SDL_CreateRenderer(win2, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if(ren1 == nullptr){
		SDL_DestroyWindow(win1);
		std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
		system("PAUSE");
		SDL_Quit();
		return 1;
	}
	if(ren2 == nullptr){
		SDL_DestroyWindow(win2);
		std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
		system("PAUSE");
		SDL_Quit();
		return 1;
	}

	std::string imagePath = "../bsod.bmp";
	SDL_Surface *bmp1 = SDL_LoadBMP(imagePath.c_str());
	std::string imagePath2 = "../hello.bmp";
	SDL_Surface *bmp2 = SDL_LoadBMP(imagePath2.c_str());
	if(bmp1 == nullptr||bmp2 == nullptr){
		SDL_DestroyWindow(win1);
		SDL_DestroyRenderer(ren1);
		std::cout << "SDL_LoadBMP Error: " << SDL_GetError() << std::endl;
		system("PAUSE");
		SDL_Quit();
		return 1;
	}

	SDL_Texture *tex1 = SDL_CreateTextureFromSurface(ren1, bmp1);
	SDL_Texture *tex2 = SDL_CreateTextureFromSurface(ren2, bmp2);
	SDL_FreeSurface(bmp1);
	SDL_FreeSurface(bmp2);
	if(tex1 == nullptr){
		SDL_DestroyWindow(win1);
		SDL_DestroyRenderer(ren1);
		std::cout << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
		system("PAUSE");
		SDL_Quit();
		return 1;
	}
	if(tex2 == nullptr){
		SDL_DestroyWindow(win2);
		SDL_DestroyRenderer(ren2);
		std::cout << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
		system("PAUSE");
		SDL_Quit();
		return 1;
	}

	SDL_Rect dst1;
	SDL_Rect dst2;
	dst1.x = 0;
	dst1.y = 0;
	dst1.w = 640;
	dst1.h = 480;
	dst2=dst1;
	for(int i = 0; i < 100; i++){
		SDL_RenderClear(ren1);
		SDL_RenderClear(ren2);
	//	dst1.x = 7 * i;
		dst1.y = 5 * i;
		//dst2.x = 7 * i*-1;
		dst2.y = 5 * i*-1;
		SDL_RenderCopy(ren1, tex1, nullptr, &dst1);
		SDL_RenderCopy(ren2, tex2, nullptr, &dst2);
		SDL_RenderPresent(ren1);
		SDL_RenderPresent(ren2);
		SDL_Delay(50);
	}
	SDL_DestroyTexture(tex1);
	SDL_DestroyTexture(tex2);
	SDL_DestroyRenderer(ren1);
	SDL_DestroyRenderer(ren2);
	SDL_DestroyWindow(win1);
	SDL_DestroyWindow(win2);

	std::cout<<"End main before SDL_Quit"<< std::endl;
	SDL_Quit();
	std::cout<<"End main after SDL_Quit"<< std::endl;
	system("PAUSE");
	return EXIT_SUCCESS;
}