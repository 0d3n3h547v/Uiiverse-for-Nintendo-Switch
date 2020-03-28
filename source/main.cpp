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

void openUiiverse();

// Main program entrypoint
int main(int argc, char* argv[])
{
	
	romfsInit();
    SDL_Init(SDL_INIT_EVERYTHING);
	IMG_Init(IMG_INIT_PNG);
	
	window = SDL_CreateWindow("n/a", 0, 0, 1280, 720, 0);
	renderer = SDL_CreateRenderer(window, 0, SDL_RENDERER_ACCELERATED);
	
	bool isApp = true;
	
    if (!(appletGetAppletType() == AppletType_Application)) {
		if (appletWarning(window, renderer) == true) {
			
			SDL_DestroyRenderer(renderer);
			SDL_DestroyWindow(window);
			
			IMG_Quit();
			SDL_Quit();
			romfsExit();
			
			isApp = false;
			return (0);
		}
	}
	
	TTF_Init();
	
	background = IMG_LoadTexture(renderer, "romfs:/background.png");
	
	SDL_Texture * icon = IMG_LoadTexture(renderer, "romfs:/uiiverse.png");
	
	SDL_Rect icon_rect;
	
	Helper_StructRect(&icon_rect, 100, 100, 115, 100);
	
	SDL_StructText TITLE;
	Helper_CreateTextureFromText(renderer, &TITLE, "Uiiverse", "romfs:/aquawax.ttf", 100, 100, 220, white);
	
	SDL_StructText COMMENT_CONTINUE;
	Helper_CreateTextureFromText(renderer, &COMMENT_CONTINUE, "Press (A) to continue", "romfs:/aquawax.ttf", 36, 500, 100, white);
	
	SDL_StructText COMMENT_QUIT;
	Helper_CreateTextureFromText(renderer, &COMMENT_QUIT, "Press (+) to quit", "romfs:/aquawax.ttf", 36, 540, 100, white);
	
    //printf(CONSOLE_RESET "Copyright (c) Uiiverse, 2019\n\nReleased under the AGPLv3.\nNot licensable under later versions and clause 7b and 7c are in effect.");

    while (appletMainLoop())
    {
        hidScanInput();
        u64 kDown = hidKeysDown(CONTROLLER_P1_AUTO);

        if (kDown & KEY_PLUS) break;

        if (kDown & KEY_A) {
            if (isApp) { 					
				openUiiverse(window, renderer); 
				break;
			}
		}
		
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, background, NULL, NULL);
		SDL_RenderCopy(renderer, icon, NULL, &icon_rect);
		SDL_RenderCopy(renderer, TITLE.txt_texture, NULL, &TITLE.txt_rect);
		SDL_RenderCopy(renderer, COMMENT_CONTINUE.txt_texture, NULL, &COMMENT_CONTINUE.txt_rect);
		SDL_RenderCopy(renderer, COMMENT_QUIT.txt_texture, NULL, &COMMENT_QUIT.txt_rect);
		SDL_RenderPresent(renderer);
    }
	
	Helper_DestroyStructText(&TITLE);
	Helper_DestroyStructText(&COMMENT_CONTINUE);
	Helper_DestroyStructText(&COMMENT_QUIT);
	
	SDL_DestroyTexture(icon);
	SDL_DestroyTexture(background);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
	romfsExit();
	
    return (EXIT_SUCCESS);
}