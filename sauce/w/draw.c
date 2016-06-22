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
#include "draw.h"

static void draw_g_entity(struct w_indow* W, unsigned id)
{
	struct g_entity* e;
	union z_jojo* j;
	/* FIXME: */
	unsigned char color[4] = {255, 0, 0, 128};

	int p[2];

	e = g_entity_get(W->G, id);
	j = z_jojo_get(&W->G->Z, id);

	if (e->type == G_E_NAUGHT || j->type == Z_J_NAUGHT)
		return;

	switch (j->type)
	{
	case Z_J_BOXXY:
		r_moveto(&W->R, j->boxxy.p);
		//r_rect_fill(&W->R, j->boxxy.l, color);
		break;

	case Z_J_PIXXY:
		r_moveto(&W->R, j->pixxy.p);
		break;

	default:
		assert(false);
	}

#define S(x, i, j) r_ssheet_draw(&W->R, W_SSHEET_ ## x, (i), (j), 0)
#define A(x, y, t) r_ssanim_draw(&W->R, W_SSANIM_ ## x ## _ ## y, (t), 2)

	switch (e->type)
	{
	case G_E_AILIN:
		A(AILIN, MONGOL, e->t);
		break;

	case G_E_LEVEL_CLARICE:
		S(LEVEL_CLARICE, 0, 0);
		break;

	case G_E_PACSATAN:
		A(PACSATAN, NHAC, e->t);
		break;

	case G_E_LEVEL_LABYRINTH:
		S(LEVEL_LABYRINTH, 0, 0);
		break;

	case G_E_LEVEL_ROOM:
		S(LEVEL_ROOM, 0, 0);
		break;

	case G_E_CHARA:
		p[0] = j->boxxy.p[0] + j->boxxy.l[0];
		p[1] = j->boxxy.p[1] + j->boxxy.l[1];
		r_moveto(&W->R, p);
		A(CHARA, DEFAULT, e->t);
		break;

	default:
		assert (false);
	}

#undef A
#undef S
}

static void draw_g_entities(struct w_indow* W)
{
	unsigned i;

	for (i = 0; i < G_E_MAX; ++i)
		draw_g_entity(W, i);
}

void w_draw(struct w_indow* W)
{
	draw_g_entities(W);
}
