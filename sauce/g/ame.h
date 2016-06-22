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

#ifndef HAS_G_AME_H
#define HAS_G_AME_H

#include <stdbool.h>
#include "z/awarudo.h"

#define G_E_MAX 16

enum g_e_type
{
	G_E_NAUGHT = 0,
	G_E_AILIN,
	G_E_LEVEL_CLARICE,
	G_E_BOMB,
	G_E_FIRE,
	G_E_PACSATAN,
	G_E_LEVEL_LABYRINTH,
	G_E_LEVEL_ROOM,
	G_E_CHARA,
	G_E_TYPE_COUNT
};

struct g_entity
{
	enum g_e_type type;
	/* FIXME: perhaps this is kinda retarded? need sleep */
	unsigned long t;
};

struct g_ame
{
	unsigned state;
	bool gameover;
	struct z_awarudo Z;
	struct g_entity entity_v[G_E_MAX];
};

#define G_E_PLAYER_ID 1
#define G_E_LEVEL_ID  0

#define g_entity_get(G, id) (&(G)->entity_v[(id)])
#define g_entity_clear(G) memset((G)->entity_v, 0, sizeof ((G)->entity_v));

void g_frame(struct g_ame* G, unsigned long dt);
void g_fini(struct g_ame* G);
void g_init(struct g_ame* G);

#endif
