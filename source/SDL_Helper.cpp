#include "include/SDL_Helper.h"

void Helper_CreateTextureFromText(SDL_Renderer *r, Helper_StructText *st, const char*text, const char*p, int size, int y, int x, SDL_Color color) {
	
	Helper_StructText pd;
	pd.txt_font = TTF_OpenFont(p, size);

	SDL_Surface * s = TTF_RenderText_Solid(pd.txt_font, text, color);
	pd.txt_texture = SDL_CreateTextureFromSurface(r, s);
	SDL_FreeSurface(s);
	
	TTF_SizeText(pd.txt_font, text, &pd.txt_rect.w, &pd.txt_rect.h);
	
	pd.txt_rect.y = y; // vertical point
	pd.txt_rect.x = x; // horizontal point
	
	memcpy(st, &pd, sizeof(pd));
	
	return;
}

void Helper_DestroyStructText(Helper_StructText * st) {
	SDL_DestroyTexture(st->txt_texture);
	TTF_CloseFont(st->txt_font);
	return;
}

void Helper_CopyRectStruct(SDL_Rect * spt1, SDL_Rect spt2) {
	
	SDL_Rect rect;
	
	rect.y = spt2.y;
	rect.x = spt2.x;
	rect.w = spt2.w;
	rect.h = spt2.h;
	
	memcpy(spt1, &rect, sizeof(rect));
	
	return;
}

void Helper_StructRect(SDL_Rect * rect, int y, int x, int w, int h) {
	
	SDL_Rect r;
	
	r.y = y;
	r.x = x;
	r.w = w;
	r.h = h;
	
	memcpy(rect, &r, sizeof(r));
	
	return;
}