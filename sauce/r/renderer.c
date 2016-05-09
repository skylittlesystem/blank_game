/*
 * Copyright (c) 2016 LUDIN
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 *
 */

#include <assert.h>
#include <SDL_image.h>
#include "renderer.h"

#define WINDOW_SCALE 4
#define R_SDL_WINDOW_TITLE "!!!11!1!!1ONE!!"
#define R_SDL_WINDOW_W (WINDOW_SCALE * R_WINDOW_W)
#define R_SDL_WINDOW_H (WINDOW_SCALE * R_WINDOW_H)

void r_op_exe(struct r_op* op)
{
	assert (op->sdl_renderer);
	assert (op->sdl_texture);

	SDL_RenderCopy(
			op->sdl_renderer,
			op->sdl_texture,
			&op->sdl_srcrect,
			&op->sdl_dstrect
			);
}

void r_ssheet_2_op(
		struct r_renderer* R,
		unsigned ssheet_id,
		unsigned i,
		unsigned j,
		struct r_op* op
		)
{
	struct r_ssheet* ssheet;

	op->sdl_renderer = R->sdl_renderer;

	ssheet = r_get_ssheet(R, ssheet_id);

	i %= ssheet->m;
	j %= ssheet->n;

	op->sdl_texture = ssheet->sdl_texture;
	op->sdl_srcrect = (struct SDL_Rect)
	{
		ssheet->sw * j,
		ssheet->sh * i,
		ssheet->sw,
		ssheet->sh
	};
}

void r_ssheet_anim_2_op(
		struct r_renderer* R,
		unsigned ssheet_id,
		unsigned long t,
		struct r_op* op
		)
{
	struct r_ssheet* ssheet;
	unsigned i, j;

	ssheet = r_get_ssheet(R, ssheet_id);
	i = (t * R_SSHEET_ANIM_FPS) / 1000;
	j = i % ssheet->n;
	i /= ssheet->n;

	r_ssheet_2_op(R, ssheet_id, i, j, op);
}

void r_ssheet_load(
		struct r_renderer* R,
		unsigned ssheet_id,
		char* path,
		unsigned sw,
		unsigned sh
		)
{
	SDL_Surface* surf;
	SDL_Texture* tex;
	struct r_ssheet* ssheet;

	surf = IMG_Load(path);
	assert (surf); /* TODO: handling */
	tex = SDL_CreateTextureFromSurface(R->sdl_renderer, surf);
	assert (tex); /* TODO: handling */
	SDL_FreeSurface(surf);

	ssheet = r_get_ssheet(R, ssheet_id);
	ssheet->sdl_texture = tex;
	ssheet->sw = sw;
	ssheet->sh = sh;
	ssheet->m = surf->h / sh;
	ssheet->n = surf->w / sw;
}

void r_renderer_clear(struct r_renderer* R)
{
	SDL_SetRenderDrawColor(R->sdl_renderer, 168, 230, 255, 255);
	SDL_RenderClear(R->sdl_renderer);
}

void r_renderer_present(struct r_renderer* R)
{
	SDL_RenderPresent(R->sdl_renderer);
}

void r_renderer_fini(struct r_renderer* R)
{
	SDL_DestroyRenderer(R->sdl_renderer);
	SDL_DestroyWindow(R->sdl_window);
	SDL_QuitSubSystem(SDL_INIT_VIDEO);
}

void r_renderer_init(struct r_renderer* R)
{
	assert(SDL_InitSubSystem(SDL_INIT_VIDEO) == 0);

	R->sdl_window = SDL_CreateWindow(
			R_SDL_WINDOW_TITLE,
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			R_SDL_WINDOW_W,
			R_SDL_WINDOW_H,
			0
			);

	assert (R->sdl_window); /* FIXME: handle */

	R->sdl_renderer = SDL_CreateRenderer(R->sdl_window, -1, 0);

	assert (R->sdl_renderer); /* FIXME: handle */

	/* TODO: decent resource handling */
	r_ssheet_load(R, R_SS_AILIN, "data/ailin_ssheet.png", 64, 64);
	r_ssheet_load(R, R_SS_LEVEL_CLARICE, "data/level_clarice_ssheet.png", 256, 64);
	r_ssheet_load(R, R_SS_BOMB, "data/bomb_ssheet.png", 64, 64);

	SDL_RenderSetScale(R->sdl_renderer, WINDOW_SCALE, WINDOW_SCALE);
}
