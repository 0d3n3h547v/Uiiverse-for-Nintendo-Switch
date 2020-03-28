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