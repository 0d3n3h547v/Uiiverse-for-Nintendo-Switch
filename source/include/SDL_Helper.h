#ifndef SDL_HELPER_H
#define SDL_HELPER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

typedef struct {
	
	TTF_Font 	* txt_font;
	SDL_Texture * txt_texture;
	SDL_Rect 	txt_rect;
	
} Helper_StructText;

void Helper_CreateTextureFromText(SDL_Renderer *r, Helper_StructText *st, const char*text, const char*p, int size, int y, int x, SDL_Color color);
void Helper_DestroyStructText(Helper_StructText * st);

void Helper_CopyRectStruct(SDL_Rect * spt1, SDL_Rect spt2); // spt1 destination << spt2 source
void Helper_StructRect(SDL_Rect * rect, int y, int x, int w, int h);

#endif