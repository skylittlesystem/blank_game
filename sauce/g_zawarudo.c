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
#include <stdbool.h>
#include <stdio.h>

#include "g_zawarudo.h"
#include "game.h"
#include "img.h"

static unsigned long g_zw_dt = 0;
static struct g_zw_wryyy wryyy;

static bool trace_boxxy_vs_boxxy()
{
	struct g_ent* j;
	j = &g_ent[wryyy.jojo_id];
	return SDL_HasIntersection(&wryyy.boxxy, &j->boxxy);
}

static bool trace_boxxy_vs_pixxy()
{
	unsigned i, k;
	struct g_ent* j;
	SDL_Surface* jbmp;
	SDL_Rect jb, b;

	j = &g_ent[wryyy.jojo_id];
	jbmp = img[j->bmp_id];

	assert (jbmp);
	assert (jbmp->format->BytesPerPixel == 1); /* just in case =O3(3) */

	jb = j->boxxy;
	jb.w = jbmp->w; /* ! */
	jb.h = jbmp->h; /* ! */

	SDL_IntersectRect(&wryyy.boxxy, &jb, &b);

	for (i = b.y; i < b.y + b.h; ++i)
		for (k = b.x; k < b.x + b.w; ++k)
			if (((unsigned char*) jbmp->pixels)[jbmp->pitch*i+k])
				return true;

	return false;
}

static bool trace()
{
	struct g_ent* j;
	bool (*f)(SDL_Rect*, unsigned); /* =op */

	j = &g_ent[wryyy.jojo_id];

	if (j->bmp_id == 666)
		f = trace_boxxy_vs_boxxy;

	else
		f = trace_boxxy_vs_pixxy;

	return f(&wryyy.boxxy, wryyy.jojo_id);
}

static void real_frame()
{
	unsigned i, k;
	struct g_ent* s, * j;

	memset(&wryyy, 0, sizeof (wryyy));

	for (i = 0; i < G_ENT_C; ++i)
	{
		s = &g_ent[i];

		if (s->type == G_ENT_NAUGHT)
			continue;

		if (s->v[0] == 0 && s->v[1] == 0)
			continue;

		wryyy.sroller_id = i;
		wryyy.boxxy = s->boxxy;
		wryyy.boxxy.x += s->v[0];
		wryyy.boxxy.y += s->v[1];

		for (k = 0; k < G_ENT_C; ++k)
		{
			if (i == k)
				continue;

			j = &g_ent[k];

			if (j->type == G_ENT_NAUGHT)
				continue;

			wryyy.jojo_id = k;

			if (trace())
				goto i_like_gotos;
		}

		s->boxxy = wryyy.boxxy;
		continue;

i_like_gotos:
		fprintf(stderr, "(%2u, %2u): WRYYY!1!!1ONE!\n",
				wryyy.sroller_id, wryyy.jojo_id);
		s->v[0] = 0;
		s->v[1] = 0;
		g_ent_wryyy(&wryyy);
	}
}

void g_zw_frame()
{
	g_zw_dt += game.dt;

	if (g_zw_dt < G_ZW_MSPF)
		return;

	while (G_ZW_MSPF <= g_zw_dt)
	{
		real_frame();
		g_zw_dt -= G_ZW_MSPF;
	}
}

void g_zw_init()
{
	g_zw_dt = 0;
}

void g_zw_fini()
{
}
