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
#include <SDL.h>

#include "renderer.h"
#include "img.h"
#include "ani.h"

static SDL_Window* sdl_window;
static SDL_Renderer* sdl_renderer;

static SDL_Texture* tex[IMG_C];

static int pointer[2];

void r_moveto(int x, int y)
{
	pointer[0] = x;
	pointer[1] = y;
}

void r_translate(int x, int y)
{
	pointer[0] += x;
	pointer[1] += y;
}

void r_color(
		unsigned char r,
		unsigned char g,
		unsigned char b,
		unsigned char a
		)
{
	SDL_SetRenderDrawColor(sdl_renderer, r, g, b, a);
}

void r_clear()
{
	SDL_RenderClear(sdl_renderer);
}

void r_present()
{
	SDL_RenderPresent(sdl_renderer);
}

void r_subtex(unsigned id, SDL_Rect* srcrect)
{
	SDL_Rect dstrect =
	{
		pointer[0],
		pointer[1],
		srcrect->w,
		srcrect->h,
	};

	SDL_RenderCopy(sdl_renderer, tex[id], srcrect, &dstrect);
}

void r_tex(unsigned id)
{
	SDL_Rect srcrect =
	{
		0,
		0,
		0,
		0,
	};

	SDL_QueryTexture(tex[id], NULL, NULL, &srcrect.w, &srcrect.h);
	r_subtex(id, &srcrect);
}

void r_tex_load(unsigned id)
{
	tex[id] = SDL_CreateTextureFromSurface(sdl_renderer, img[id]);
}

void r_tex_load_all()
{
	unsigned i;

	for (i = 0; i < IMG_C; ++i)
		r_tex_load(i);
}

void r_tex_unload(unsigned id)
{
	SDL_DestroyTexture(tex[id]);
	tex[id] = NULL;
}

void r_tex_unload_all()
{
	unsigned i;

	for (i = 0; i < IMG_C; ++i)
		r_tex_unload(i);
}

void r_boxxy(SDL_Rect* r)
{
	SDL_RenderFillRect(sdl_renderer, r);
}

void r_ani(unsigned id, unsigned t)
{
	struct ani* a;
	struct ani_frm* f;
	SDL_Rect srcrect;
	unsigned t_c;

	a = &ani[id];

	assert (a); /* just in case ;O3 */

	t_c = a->v[a->c - 1].t;

	if (t_c == 0)
	{
		t = 0;
		f = &a->v[0];
	}

	else
	{
		t %= t_c;
		for (f = a->v; f->t <= t; ++f);
		--f;
	}

	srcrect.x = f->j * a->f_w;
	srcrect.y = f->i * a->f_h;
	srcrect.w = a->f_w;
	srcrect.h = a->f_h;

	r_translate( a->x,  a->y);
	r_subtex(a->tex_id, &srcrect);
	r_translate(-a->x, -a->y);
}

void r_init()
{
	int r;
	memset(tex, 0, sizeof (tex));
	r_moveto(0, 0);

	r = SDL_Init(SDL_INIT_VIDEO);
	assert (r == 0); /* TODO: handling */

	sdl_window = SDL_CreateWindow(
			R_TITLE,
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			R_WIN_W,
			R_WIN_H,
			0
			);

	assert (sdl_window); /* TODO: handling */

	sdl_renderer = SDL_CreateRenderer(
			sdl_window,
			-1,
			0
			);

	assert (sdl_renderer); /* TODO: handling */

	SDL_RenderSetLogicalSize(
			sdl_renderer,
			R_W,
			R_H
			);
}

void r_fini()
{
	r_tex_unload_all();
	SDL_DestroyRenderer(sdl_renderer);
	SDL_DestroyWindow(sdl_window);
	SDL_QuitSubSystem(SDL_INIT_VIDEO);
}
