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
#include <string.h>
#include "ame.h"

#include <math.h>

void g_frame(struct g_ame* G, unsigned long dt)
{
	unsigned i;
	struct g_entity* e1, * e2;
	float* p1, * p2, d[2];

	for (i = 0; i < G_E_MAX; ++i)
	{
		e1 = g_entity_get(G, i);

		if (e1->type == G_E_NAUGHT)
			continue;

		e1->t += dt;

		e1->pos[0] += (e1->vel[0] * dt) / 1000;
		e1->pos[1] += (e1->vel[1] * dt) / 1000;
	}

	e1 = g_entity_get(G, G_E_PLAYER_ID);
	e2 = g_entity_get(G, 2);
	p1 = e1->pos;
	p2 = e2->pos;
#define sqr(x) ((x) * (x))

	d[0] = p1[0] - p2[0];
	d[1] = p1[1] - p2[1];
	float dist = sqrt(sqr(d[0]) + sqr(d[1]));

	e2->vel[0] = d[0] / dist * .2 * 64;
	e2->vel[1] = d[1] / dist * .2 * 64;


	if (dist <= .5)
		G->gameover = true;

#undef sqr
}

void g_fini(struct g_ame* G)
{
	assert (G);
}

void g_init(struct g_ame* G)
{
	struct g_entity* e;

	assert (G);

	memset(G, 0, sizeof (*G));

	G->gameover = false;

	e = g_entity_get(G, G_E_PLAYER_ID);
	e->type = G_E_AILIN;
	e->vel[2] =  1 * 64;
	e->pos[0] = -1 * 64;
	e->pos[1] =  0;

	e = g_entity_get(G, G_E_LEVEL_ID);
	e->type = G_E_LEVEL_CLARICE;
	e->vel[2] =  1 * 64;
	e->pos[0] =  0;
	e->pos[1] = -1.25 * 64;

	e = g_entity_get(G, 2);
	e->type = G_E_PACSATAN;
	e->vel[2] =  1 * 64;
	e->pos[0] =  1 * 64;
	e->pos[1] =  0 * 64;
	e->pos[2] =  1 * 64;
}
