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

#ifndef HAS_R_RENDERER_H
#define HAS_R_RENDERER_H

#include <SDL.h>

struct r_ssheet
{
	SDL_Texture* sdl_texture;
	unsigned sw, sh;		/* sprite w, h */
	unsigned m, n;			/* rows, cols */
};

#define R_SSHEET_ANIM_FPS 24

struct r_renderer
{
	SDL_Window* sdl_window;
	SDL_Renderer* sdl_renderer;
	struct r_ssheet ssheet_v[16];
};

struct r_op
{
	SDL_Renderer* sdl_renderer;
	SDL_Texture* sdl_texture;
	SDL_Rect sdl_srcrect;
	SDL_Rect sdl_dstrect;
};

#define r_get_ssheet(R, id) (&(R)->ssheet_v[(id)])
/*#define r_get_g_type_ssheet(type) ((R)->g_type_ssheet_v[(type)])*/

void r_op_exe(struct r_op* op);

void r_ssheet_2_op(
		struct r_renderer* R,
		unsigned ssheet_id,
		unsigned i,
		unsigned j,
		struct r_op* op
		);

void r_ssheet_anim_2_op(
		struct r_renderer* R,
		unsigned ssheet_id,
		unsigned long t,
		struct r_op* op
		);

void r_ssheet_load(
		struct r_renderer* R,
		unsigned ssheet_id,
		char* path,
		unsigned sw,
		unsigned sh
		);

void r_renderer_clear(struct r_renderer* R);
void r_renderer_present(struct r_renderer* R);

void r_renderer_fini(struct r_renderer* R);
void r_renderer_init(struct r_renderer* R);

#endif
