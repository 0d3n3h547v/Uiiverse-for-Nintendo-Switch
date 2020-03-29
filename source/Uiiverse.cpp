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
#include <switch.h>

#include "include/Uiiverse.h"
#include "include/SDL_Helper.h"

SDL_Color white_f = {255, 255, 255, 255};

bool appletWarning(SDL_Window * window, SDL_Renderer * renderer) {
	
	SDL_Texture * texture = IMG_LoadTexture(renderer, "romfs:/warning.png");
	
	while(appletMainLoop()) {
		hidScanInput();
		u64 kDown = hidKeysDown(CONTROLLER_P1_AUTO);
		
		if (kDown & KEY_PLUS) break;
		
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, texture, NULL, NULL);
		SDL_RenderPresent(renderer);
	}
	
	SDL_DestroyTexture(texture);
	
	return true;
}

void infoUiiverse(SDL_Renderer * r, SDL_Texture * background) {
	
	SDL_RenderClear(r);
	
	Helper_StructText COMMENT_COPYRIGHT;
	Helper_CreateTextureFromText(r, &COMMENT_COPYRIGHT, "Copyright (c) Uiiverse", "romfs:/aquawax.ttf", 100, 100, 100, white_f);
	
	Helper_StructText COMMENT_UNDER;
	Helper_CreateTextureFromText(r, &COMMENT_UNDER, "(GUI by Waifro)", "romfs:/aquawax.ttf", 60, 250, 100, white_f);
	
	Helper_StructText COMMENT_RELEASE;
	Helper_CreateTextureFromText(r, &COMMENT_RELEASE, "Released under the AGPL.", "romfs:/aquawax.ttf", 40, 320, 100, white_f);
	
	Helper_StructText COMMENT_LICENSE;
	Helper_CreateTextureFromText(r, &COMMENT_LICENSE, "Not licensable under later versions", "romfs:/aquawax.ttf", 36, 400, 100, white_f);
	
	Helper_StructText COMMENT_LICENSE1;
	Helper_CreateTextureFromText(r, &COMMENT_LICENSE1, "And clause seven a/b are in effect.", "romfs:/aquawax.ttf", 36, 450, 100, white_f);
	
	Helper_StructText COMMENT_BACK;
	Helper_CreateTextureFromText(r, &COMMENT_BACK, "Back", "romfs:/aquawax.ttf", 36, 580, 100, white_f);
	
	SDL_Rect sel;
	Helper_CopyRectStruct(&sel, COMMENT_BACK.txt_rect);
	
	while(appletMainLoop()) {
		
		hidScanInput();
		u64 kDown = hidKeysDown(CONTROLLER_P1_AUTO);
		
		if (kDown & KEY_A) break;
		
		SDL_RenderClear(r);
		SDL_RenderCopy(r, background, NULL, NULL);
		SDL_RenderCopy(r, COMMENT_COPYRIGHT.txt_texture, NULL, &COMMENT_COPYRIGHT.txt_rect);
		SDL_RenderCopy(r, COMMENT_UNDER.txt_texture, NULL, &COMMENT_UNDER.txt_rect);
		SDL_RenderCopy(r, COMMENT_RELEASE.txt_texture, NULL, &COMMENT_RELEASE.txt_rect);
		SDL_RenderCopy(r, COMMENT_LICENSE.txt_texture, NULL, &COMMENT_LICENSE.txt_rect);
		SDL_RenderCopy(r, COMMENT_LICENSE1.txt_texture, NULL, &COMMENT_LICENSE1.txt_rect);
		SDL_RenderCopy(r, COMMENT_BACK.txt_texture, NULL, &COMMENT_BACK.txt_rect);
		
		SDL_RenderDrawRect(r, &sel);
		
		SDL_RenderPresent(r);
	}
	
	Helper_DestroyStructText(&COMMENT_COPYRIGHT);
	Helper_DestroyStructText(&COMMENT_UNDER);
	Helper_DestroyStructText(&COMMENT_RELEASE);
	Helper_DestroyStructText(&COMMENT_LICENSE);
	Helper_DestroyStructText(&COMMENT_LICENSE1);
	Helper_DestroyStructText(&COMMENT_BACK);
	
	return;
}

void openUiiverse(SDL_Window * w, SDL_Renderer * r) {
	
	SDL_RenderClear(r);
	SDL_DestroyRenderer(r);
	SDL_DestroyWindow(w);
	
    Result rc;
    WebCommonConfig config;

    // Create the config.
    rc = webPageCreate(&config, "https://uiiverse.xyz/");

    if (R_SUCCEEDED(rc)) {
        rc = webConfigSetWhitelist(&config, "^http*");
        if (R_SUCCEEDED(rc)) rc = webConfigShow(&config, NULL);
    }
	
	return;
}