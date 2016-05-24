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

#include "draw.h"

#define PPWU 64

static void draw_g_entity(struct w_indow* W, unsigned id)
{
	struct g_entity* e;
	int p[2];

	e = g_entity_get(W->G, id);

	p[0] = R_WIDTH  / 2 + e->pos[0];
	p[1] = R_HEIGHT / 2 - e->pos[1];

	r_identity(&W->R);
	r_translate(&W->R, p[0], p[1]);

#define S(x, i, j) r_ssheet_draw(&W->R, W_SSHEET_ ## x, (i), (j), true)

#define A(x, y, t) r_ssanim_draw(&W->R, W_SSANIM_ ## x ## _ ## y, (t), true)

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

	default:
		break;
	}

	r_translate(&W->R, -p[0], -p[1]);
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
