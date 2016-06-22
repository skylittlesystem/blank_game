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
#include <stdio.h>
#include "ame.h"


#include <math.h>

void g_on_wryyy(struct g_ame* G, struct z_wryyy* wryyy)
{
	puts("HIT");
}

void g_frame(struct g_ame* G, unsigned long dt)
{
	unsigned i;
	z_awarudo_frame(&G->Z, dt);

	for (i = 0; i < G_E_MAX; ++i)
	{
		struct g_entity* e;
		e = g_entity_get(G, i);

		if (e->type == G_E_NAUGHT)
			continue;

		e->t += dt;
	}
}

void g_fini(struct g_ame* G)
{
	assert (G);
}

void g_init(struct g_ame* G)
{
	struct g_entity* e;
	union z_jojo* j;

	assert (G);

	memset(G, 0, sizeof (*G));

	G->Z.dio = G;
	G->Z.on_wryyy = (void (*)(void*, struct z_wryyy*)) g_on_wryyy;

	G->gameover = false;

	e = g_entity_get(G, G_E_PLAYER_ID);
	j = z_jojo_get(&G->Z, G_E_PLAYER_ID);
	e->type = G_E_CHARA;
	j->type = Z_J_BOXXY;

	j->boxxy.p[0] = 70 + 73;
	j->boxxy.p[1] = 98 + 47;
	j->boxxy.l[0] = 13;
	j->boxxy.l[1] = 13;
	j->boxxy.v[0] = 0;
	j->boxxy.v[1] = 0;

	e = g_entity_get(G, G_E_LEVEL_ID);
	e->type = G_E_LEVEL_ROOM;
	z_j_pixxy_load(&G->Z, G_E_LEVEL_ID, "data/pixxy/LEVEL_ROOM");
}
