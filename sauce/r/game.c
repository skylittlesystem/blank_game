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

#include "game.h"

/* pixels per world unit */
#define PPWU 64

void r_g_entity_draw(struct r_renderer* R, struct g_game* G, unsigned id)
{
	struct r_op op;
	struct g_entity* e;
	struct r_ssheet* ssheet;
	unsigned ssheet_id;

	e = g_get_entity(G, id);

	switch (e->type)
	{
	case G_AILIN:
		ssheet_id = R_SS_AILIN;
		break;

	case G_LEVEL_CLARICE:
		ssheet_id = R_SS_LEVEL_CLARICE;
		break;

	case G_BOMB:
		ssheet_id = R_SS_BOMB;
		break;

	default:
		return;
	}

	ssheet = r_get_ssheet(R, ssheet_id);

	r_ssheet_anim_2_op(R, ssheet_id, e->t, &op);
	op.sdl_dstrect = (SDL_Rect)
	{
		(int) (R_WINDOW_W / 2 + e->pos[0] * PPWU - ssheet->sw / 2),
		(int) (R_WINDOW_H / 2 + (-e->pos[1] * PPWU) - ssheet->sh / 2),
		ssheet->sw,
		ssheet->sh,
	};

	r_op_exe(&op);
}

void r_g_game_draw(
		struct r_renderer* R,
		struct g_game* G
		)
{
	unsigned i;

	for (i = 0; i < G_MAX_ENTITIES; ++i)
		r_g_entity_draw(R, G, i);
}
