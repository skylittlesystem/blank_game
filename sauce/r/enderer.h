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

#ifndef HAS_R_ENDERER_H
#define HAS_R_ENDERER_H

#define R_WIDTH  320
#define R_HEIGHT 240

#include <SDL.h>
#include <stdbool.h>

struct r_ss_heet
{
	SDL_Texture* sdl_texture;
	unsigned sw, sh;		/* sprite w, h */
	unsigned m, n;			/* rows, cols */
};

#define R_SS_ANIM_FPS 10

struct r_ss_anim
{
	unsigned ssheet_id;
	unsigned (*frame_v)[2];
	unsigned frame_c;
};

struct r_enderer
{
	SDL_Window* sdl_window;
	SDL_Renderer* sdl_renderer;
	int sdl_dstrect_translate[2];
	struct r_ss_heet ssheet_v[16];
	struct r_ss_anim ssanim_v[128];
};

void r_identity(struct r_enderer* R);
void r_translate(struct r_enderer* R, int x, int y);

#define r_ssheet_get(R, id) (&(R)->ssheet_v[(id)])
#define r_ssanim_get(R, id) (&(R)->ssanim_v[(id)])

void r_ssheet_draw(
		struct r_enderer* R,
		unsigned id,
		unsigned i,
		unsigned j,
		bool center
		);

void r_ssanim_draw(
		struct r_enderer* R,
		unsigned id,
		unsigned long t,
		bool center
		);

void r_ssheet_load(
		struct r_enderer* R,
		unsigned id,
		char* path
		);

void r_ssanim_load(
		struct r_enderer* R,
		unsigned id,
		char* path,
		unsigned ssheet_id
		);

void r_clear(struct r_enderer* R);
void r_present(struct r_enderer* R);

void r_fini(struct r_enderer* R);
void r_init(struct r_enderer* R);

#endif