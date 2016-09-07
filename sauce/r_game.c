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

#include "renderer.h"
#include "game.h"
#include "r_game.h"
#include "r_g_dialog.h"

static int type_2_ani[G_ENT_TYPE_C] =
{
	0,
	1,
	2,
	3,
	4,
	5,
	6,
	7,
	8,
	9,
	10,
	11,
	12,
	13,
	14,
	15,
	16,
	17,
	18,
	0,
	20,
	0,
	22,
	0,
	24,
};

static unsigned z_order[G_ENT_C] =
{
	0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
	20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31
};
static bool show_boxxies = false;

static int z_cmp(const unsigned* id_a, const unsigned* id_b)
{
	struct g_ent* a, * b;

	a = &g_ent[*id_a];
	b = &g_ent[*id_b];

	/* DESC sort. -1 is over 0 */
	if (a->z > b->z) return -1;
	if (a->z < b->z) return 1;
	if (a->boxxy.y < b->boxxy.y) return -1;
	if (a->boxxy.y > b->boxxy.y) return 1;
	return 0;
}

void r_g_toggle_boxxies()
{
	show_boxxies = !show_boxxies;
}

void r_g_ent(unsigned i)
{
	struct g_ent* e;
	e = &g_ent[i];

	if (e->type == G_ENT_NAUGHT)
		return;

	SDL_Rect boxxy = {
		e->boxxy.x + R_W/2 - g_ent[0].boxxy.x,
		e->boxxy.y + R_H/2 - g_ent[0].boxxy.y,
		e->boxxy.w,
		e->boxxy.h
	};

	r_moveto(boxxy.x, boxxy.y);

	if (show_boxxies)
	{
		r_color(255, 0, 0, 255);
		r_boxxy(&boxxy);
	}

	r_ani(type_2_ani[e->type], game.t);
}

void r_g_lvl()
{
	unsigned i;

	qsort(z_order, G_ENT_C, sizeof (z_order[0]),
			(int (*)(const void*, const void*)) z_cmp);

	for (i = 0; i < G_ENT_C; ++i)
		r_g_ent(z_order[i]);
}

void r_game()
{
	r_g_lvl();
	r_g_dialog();
}
