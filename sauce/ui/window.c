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

#include "window.h"
#include "r/game.h"

enum keybit
{
	KB_NAUGHT =	0,
	KB_RIGHT =	2,
	KB_UP =		4,
	KB_LEFT =	8,
	KB_DOWN =	16,
	KB_z =		32
};

static unsigned char keycode_2_keybit(SDL_Keycode sym)
{
	switch (sym)
	{
	case SDLK_RIGHT:	return KB_RIGHT;
	case SDLK_UP:		return KB_UP;
	case SDLK_LEFT:		return KB_LEFT;
	case SDLK_DOWN:		return KB_DOWN;
	case SDLK_z:		return KB_z;
	default:		return KB_NAUGHT;
	}

	return 0;
}

void ui_window_event(struct ui_window* win, SDL_Event* e)
{
	unsigned char bit = keycode_2_keybit(e->key.keysym.sym);
	switch (e->type)
	{
	case SDL_KEYUP:
		win->keyv &= ~bit;
		return;

	case SDL_KEYDOWN:
		win->keyv |= bit;
		return;
	}
	
}

void ui_process_keys(struct ui_window* win)
{
	struct g_entity* e;

	e = g_get_player_entity(win->G);

	memset(e->vel, 0, sizeof (e->vel));

	/* FIXME: velocity should be capped by game */
#define V .5
	e->vel[0] += (win->keyv & KB_RIGHT) ?	 V : 0;
	e->vel[1] += (win->keyv & KB_UP) ?	 V : 0;
	e->vel[0] += (win->keyv & KB_LEFT) ?	 -V : 0;
	e->vel[1] += (win->keyv & KB_DOWN) ?	 -V : 0;
#undef V
}

void ui_window_draw(struct ui_window* win, unsigned long dt)
{
	r_g_game_draw(&win->R, win->G);
}

void ui_window_frame(struct ui_window* win, unsigned long dt)
{
	r_renderer_clear(&win->R);
	ui_process_keys(win);
	ui_window_draw(win, dt);
	r_renderer_present(&win->R);
}

void ui_window_fini(struct ui_window* win)
{
	r_renderer_fini(&win->R);
}

void ui_window_init(struct ui_window* win, struct g_game* G)
{
	r_renderer_init(&win->R);
	win->G = G;
}
