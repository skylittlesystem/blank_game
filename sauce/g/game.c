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
#include "game.h"

void g_game_frame(struct g_game* G, unsigned long dt)
{
	unsigned i;

	for (i = 0; i < G_MAX_ENTITIES; ++i)
	{
		struct g_entity* e;

		e = g_get_entity(G, i);

		if (e == G_NAUGHT)
			continue;

		e->pos[0] += (e->vel[0] * dt) / 1000;
		e->pos[1] += (e->vel[1] * dt) / 1000;
	}
}

void g_game_fini(struct g_game* G)
{
	assert (G);
}

void g_game_init(struct g_game* G)
{
	struct g_entity* e;

	assert (G);

	memset(G, 0, sizeof (*G));

	e = g_get_entity(G, 0);
	e->type = G_AILIN;
	e->pos[0] = 10;
	e->pos[1] = 30;
}
