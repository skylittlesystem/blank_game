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

#include "indow.h"
#include "draw.h"

static void handle_events(struct w_indow* W)
{
	SDL_Event e;
	struct g_entity* p1;

	(void) p1;

	p1 = g_entity_get(W->G, G_E_PLAYER_ID);

	while (SDL_PollEvent(&e))
	{
		switch (e.type)
		{
		case SDL_KEYDOWN:
			switch (e.key.keysym.sym)
			{
			default:
				break;
			}
			break;

		case SDL_KEYUP:
			switch (e.key.keysym.sym)
			{
			case SDLK_z:
				break;
			}
			break;

		case SDL_QUIT:
			W->G->gameover = true;
			return;

		default:
			continue;
		}
	}
}

static void handle_keyboard_state(struct w_indow* W)
{
	const Uint8* s;
	//struct g_entity* e;
	struct z_j_boxxy* jb;

	s = SDL_GetKeyboardState(NULL);
	//e = g_entity_get(W->G, G_E_PLAYER_ID);
	jb = &z_jojo_get(&W->G->Z, G_E_PLAYER_ID)->boxxy;

	memset(jb->v, 0, sizeof (jb->v));

	/* FIXME: velocity should be capped by game */
#define V 1
	jb->v[0] += (s[SDL_SCANCODE_RIGHT]) ?	 V : 0;
	jb->v[1] += (s[SDL_SCANCODE_UP]) ?	-V : 0;
	jb->v[0] += (s[SDL_SCANCODE_LEFT]) ?	-V : 0;
	jb->v[1] += (s[SDL_SCANCODE_DOWN]) ?	 V : 0;
#undef V
}

#include "assets.c"

void w_frame(struct w_indow* W, unsigned long dt)
{
	handle_events(W);
	handle_keyboard_state(W);

	r_clear(&W->R);
	w_draw(W);
	r_present(&W->R);
}

void w_fini(struct w_indow* W)
{
	m_ixer_fini(&W->M);
	r_fini(&W->R);
}

void w_init(struct w_indow* W, struct g_ame* G)
{
	r_init(&W->R);
	m_ixer_init(&W->M);

	load_assets(W);

	W->G = G;
}
