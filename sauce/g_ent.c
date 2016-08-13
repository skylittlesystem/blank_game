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
#include <stdio.h>

#include "game.h"
#include "g_ent.h"

struct g_ent g_ent[G_ENT_C];

static void g_ent_pacsatan_think(unsigned id)
{
	struct g_ent* pacsatan, * clarice;

	pacsatan = &g_ent[id];
	assert (pacsatan);

	clarice = &g_ent[pacsatan->target_id];
	assert (clarice);

	pacsatan->v[0] = clarice->boxxy.x - pacsatan->boxxy.x;
	pacsatan->v[1] = clarice->boxxy.y - pacsatan->boxxy.y;

	if (pacsatan->v[0])
		pacsatan->v[0] /= abs(pacsatan->v[0]);

	if (pacsatan->v[1])
		pacsatan->v[1] /= abs(pacsatan->v[1]);

	pacsatan->v[0] *= 3;
	pacsatan->v[1] *= 3;
}

static void g_ent_pacsatan_wryyy(unsigned id, struct g_zw_wryyy* wryyy)
{
	struct g_ent* pacsatan;

	pacsatan = &g_ent[id];
	assert (pacsatan);

	if (
			wryyy->sroller_id != pacsatan->target_id &&
			wryyy->jojo_id != pacsatan->target_id
	   )
		return;


	g_quit();
}

/* dispatch tables */
static void (*type_2_think[G_ENT_TYPE_C])(unsigned) =
{
	NULL,
	NULL,
	g_ent_pacsatan_think,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
};

static void (*type_2_wryyy[G_ENT_TYPE_C])(unsigned, struct g_zw_wryyy*) =
{
	NULL,
	NULL,
	g_ent_pacsatan_wryyy,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
};

/* dispatch helpers */
static void g_ent_think(unsigned id)
{
	struct g_ent* e;

	e = &g_ent[id];

	if (!e->type)
		return;

	if (type_2_think[e->type])
		type_2_think[e->type](id);
}	

void g_ent_wryyy(struct g_zw_wryyy* wryyy)
{
	struct g_ent* sroller, * jojo;

	sroller = &g_ent[wryyy->sroller_id];
	assert (sroller->type);

	jojo = &g_ent[wryyy->jojo_id];
	assert (jojo->type);

	if (type_2_wryyy[sroller->type])
		type_2_wryyy[sroller->type](wryyy->sroller_id, wryyy);

	if (type_2_wryyy[jojo->type])
		type_2_wryyy[jojo->type](wryyy->jojo_id, wryyy);
}

void g_ent_frame()
{
	unsigned i;
	for (i = 0; i < G_ENT_C; ++i)
		g_ent_think(i);
}
