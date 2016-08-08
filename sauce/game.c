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
#include "g_zawarudo.h"
#include "g_ent.h"

unsigned long g_t, g_dt;

#define FMT "save/%u"

char* const const g_path_fmt = FMT "/game.txt";
const char* const g_lvl_path_fmt[G_LVL_C] =
{
	FMT "/lvl_clarice.txt",
	FMT "/lvl_labyrinth.txt",
	FMT "/lvl_room.txt",
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
};

unsigned g_id;
struct game game;

unsigned g_lvl_id;
struct g_lvl g_lvl;

/* lvl */
static const char* g_lvl_path(unsigned id)
{
	static char s[1024];
	sprintf(s, g_lvl_path_fmt[id], g_id);
	return s;
}

static void g_lvl_slurp(unsigned id)
{
	FILE* fp;

	fp = fopen(g_lvl_path(id), "r");
	assert (fp); /* TODO: handling */

	while (!feof(fp))
	{
		unsigned id;
		struct g_ent* e;

		assert (fscanf(fp, " %u ", &id) == 1); /* TODO: handling */
		e = &g_ent[id];

		assert (
			fscanf(
				fp,
				" %u %d %d %u %u %d %d %u %u ",
				&e->type,
				&e->boxxy.x,
				&e->boxxy.y,
				&e->boxxy.w,
				&e->boxxy.h,
				&e->v[0],
				&e->v[1],
				&e->bmp_id,
				&e->target_id
			      )
			== 9
		       ); /* TODO: handling */
	}

	fclose(fp);
}

void g_lvl_load(unsigned id)
{
	g_lvl_slurp(id);
	g_zw_init();
}

/* game */
#define V 4
void g_in_arrows(bool r, bool u, bool l, bool d)
{
	struct g_ent* e;
	e = &g_ent[0];

	e->v[0] = 0;
	e->v[1] = 0;

	e->v[0] += r ? V : 0;
	e->v[1] -= u ? V : 0;
	e->v[0] -= l ? V : 0;
	e->v[1] += d ? V : 0;

}

void g_in_x()
{
}

void g_in_z()
{
}

static void g_tick()
{
	g_dt = SDL_GetTicks() - g_t;
	g_t += g_dt;
}

void g_frame()
{
	g_tick();
	g_zw_frame();
	g_ent_frame();
}

static const char* g_path(unsigned id)
{
	static char s[1024];
	sprintf(s, g_path_fmt, id);
	return s;
}

static void g_slurp(unsigned id)
{
	FILE* fp;

	fp = fopen(g_path(id), "r");
	assert (fp); /* TODO: handling */

	assert (fscanf(fp, " %u ", &game.lvl_id) == 1); /* TODO: handling */

	fclose(fp);
}

void g_load(unsigned id)
{
	g_id = id;
	g_slurp(id);
	g_lvl_load(game.lvl_id);
}

void g_init()
{
	memset(&game, 0, sizeof (game));
	memset(&g_lvl, 0, sizeof (g_lvl));
	memset(&g_ent, 0, sizeof (g_ent));

	g_t = 0;
	g_dt = 0;
}

void g_fini()
{
}
