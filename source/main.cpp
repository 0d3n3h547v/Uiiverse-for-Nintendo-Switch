/*  Uiiverse for Switch
    Copyright (C) 2019, Uiiverse.

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Affero General Public License as published
    by the Free Software Foundation at version 3 of the License.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Affero General Public License for more details.

    You should have received a copy of the GNU Affero General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.

    In addition, the following extra clauses are in effect:

    7b) Requiring preservation of specified reasonable legal notices or
    author attributions in that material or in the Appropriate Legal
    Notices displayed by works containing it;

    7c) Prohibiting misrepresentation of the origin of that material, or
    requiring that modified versions of such material be marked in
    reasonable ways as different from the original version;
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <switch.h>

#include "include/Uiiverse.h"
#include "include/SDL_Helper.h"

SDL_Window * window;
SDL_Renderer * renderer;
SDL_Texture * background;

SDL_Color white = {255, 255, 255, 255};
SDL_Color red = {255, 0, 0, 255};

// Main program entrypoint
int main(int argc, char* argv[])
{
	
	romfsInit();
    SDL_Init(SDL_INIT_EVERYTHING);
	IMG_Init(IMG_INIT_PNG);
	Mix_Init(MIX_INIT_MP3);
	
	window = SDL_CreateWindow("n/a", 0, 0, 1280, 720, 0);
	renderer = SDL_CreateRenderer(window, 0, SDL_RENDERER_ACCELERATED);
	
	bool isApp = false;
	
    if (!(appletGetAppletType() == AppletType_Application)) {
		if (appletWarning(window, renderer) == true) {
			
			SDL_DestroyRenderer(renderer);
			SDL_DestroyWindow(window);
			
			IMG_Quit();
			SDL_Quit();
			romfsExit();
			
			return (0);
		}
	}
	
	TTF_Init();
	
	background = IMG_LoadTexture(renderer, "romfs:/background.png");
	
	SDL_Texture * icon = IMG_LoadTexture(renderer, "romfs:/uiiverse.png");
	
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);
	
	Mix_Music * music;
	music = Mix_LoadMUS("romfs:/music.mp3");
	
	SDL_Rect icon_rect;
	
	Helper_StructRect(&icon_rect, 100, 100, 115, 100);
	
	Helper_StructText TITLE;
	Helper_CreateTextureFromText(renderer, &TITLE, "Uiiverse", "romfs:/aquawax.ttf", 100, 100, 220, white);
	
	Helper_StructText COMMENT_CONTINUE;
	Helper_CreateTextureFromText(renderer, &COMMENT_CONTINUE, "Continue", "romfs:/aquawax.ttf", 36, 500, 100, white);
	
	Helper_StructText COMMENT_INFO;
	Helper_CreateTextureFromText(renderer, &COMMENT_INFO, "Information", "romfs:/aquawax.ttf", 36, 540, 100, white);
	
	Helper_StructText COMMENT_QUIT;
	Helper_CreateTextureFromText(renderer, &COMMENT_QUIT, "Quit", "romfs:/aquawax.ttf", 36, 580, 100, white);
	
	SDL_Rect select;
	Helper_CopyRectStruct(&select, COMMENT_CONTINUE.txt_rect);
	
	Helper_StructText ERROR;
	Helper_CreateTextureFromText(renderer, &ERROR, "Warning: it will crash the homebrew", "romfs:/aquawax.ttf", 28, 650, 50, red);
	
	Mix_PlayMusic(music, -1);
	
	
    while (appletMainLoop())
    {
        hidScanInput();
        u64 kDown = hidKeysDown(CONTROLLER_P1_AUTO);

        if (kDown & KEY_DUP) {
			if (select.y == (COMMENT_QUIT.txt_rect.y)) Helper_CopyRectStruct(&select, COMMENT_INFO.txt_rect);
			else if (select.y == (COMMENT_INFO.txt_rect.y)) Helper_CopyRectStruct(&select, COMMENT_CONTINUE.txt_rect);
		}
		
		if (kDown & KEY_DDOWN) {
			if (select.y == (COMMENT_CONTINUE.txt_rect.y)) Helper_CopyRectStruct(&select, COMMENT_INFO.txt_rect);
			else if (select.y == (COMMENT_INFO.txt_rect.y)) Helper_CopyRectStruct(&select, COMMENT_QUIT.txt_rect);
		}
		
        if (kDown & KEY_A) {
			
			if (select.y == (COMMENT_CONTINUE.txt_rect.y)) {
				isApp = true;
				break;
			}
			
			if (select.y == (COMMENT_INFO.txt_rect.y)) {
				Helper_CopyRectStruct(&select, COMMENT_CONTINUE.txt_rect);
				infoUiiverse(renderer, background);
			}
			
			if (select.y == (COMMENT_QUIT.txt_rect.y)) break;
		}
		
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, background, NULL, NULL);
		SDL_RenderCopy(renderer, icon, NULL, &icon_rect);
		SDL_RenderCopy(renderer, TITLE.txt_texture, NULL, &TITLE.txt_rect);
		SDL_RenderCopy(renderer, COMMENT_CONTINUE.txt_texture, NULL, &COMMENT_CONTINUE.txt_rect);
		SDL_RenderCopy(renderer, COMMENT_INFO.txt_texture, NULL, &COMMENT_INFO.txt_rect);
		SDL_RenderCopy(renderer, COMMENT_QUIT.txt_texture, NULL, &COMMENT_QUIT.txt_rect);
		SDL_RenderCopy(renderer, ERROR.txt_texture, NULL, &ERROR.txt_rect);
		
		SDL_RenderDrawRect(renderer, &select);
		
		SDL_RenderPresent(renderer);
    }
	
	Helper_DestroyStructText(&TITLE);
	Helper_DestroyStructText(&COMMENT_CONTINUE);
	Helper_DestroyStructText(&COMMENT_INFO);
	Helper_DestroyStructText(&COMMENT_QUIT);
	Helper_DestroyStructText(&ERROR);
	
	Mix_CloseAudio();
	Mix_FreeMusic(music);
	
	SDL_DestroyTexture(icon);
	SDL_DestroyTexture(background);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	
	Mix_Quit();
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
	romfsExit();
	
	if (isApp == true) openUiiverse();
	
    return (EXIT_SUCCESS);
}