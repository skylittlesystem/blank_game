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

static int type_2_ani[G_ENT_TYPE_C] =
{
	0,
	1,
	2,
	0,
	0,
	0,
};

void r_g_ent(unsigned i)
{
	struct g_ent* e;
	e = &g_ent[i];

	if (e->type == G_ENT_NAUGHT)
		return;

	r_moveto(e->boxxy.x, e->boxxy.y);
	r_ani(type_2_ani[e->type], g_t);
}

void r_g_lvl()
{
	unsigned i;

	for (i = 0; i < G_ENT_C; ++i)
		r_g_ent(i);
}

void r_game()
{
	r_g_lvl();
}
