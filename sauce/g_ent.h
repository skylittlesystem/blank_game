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

#ifndef HAS_G_ENT_H
#define HAS_G_ENT_H

enum g_ent_type
{
	G_ENT_NAUGHT = 0,
	G_ENT_AILIN,
	G_ENT_PACSATAN,
	G_ENT_LEVEL_CLARICE,
	G_ENT_LEVEL_LABYRINTH,
	G_ENT_LEVEL_ROOM_CLOTHES_RACK = 10,
	G_ENT_LEVEL_ROOM_CHAIR,
	G_ENT_LEVEL_ROOM_BED,
	G_ENT_LEVEL_ROOM_BOOKS = 15,
	G_ENT_LEVEL_ROOM_PC,
	G_ENT_CHARA,
	G_ENT_LEVEL_ROOM_BACKGROUND,
	G_ENT_LEVEL_CORRIDOR_BACKGROUND_LEFT = 20,
	G_ENT_LEVEL_CORRIDOR_BACKGROUND_RIGHT = 22,
	G_ENT_LEVEL_CORRIDOR_BACKGROUND_MIDDLE = 24,
	G_ENT_TYPE_C
};

struct g_ent
{
	enum g_ent_type type;
	SDL_Rect boxxy;
	int z;
	int v[2];
	unsigned bmp_id;
	unsigned target_id;
};

#define G_ENT_C 32
extern struct g_ent g_ent[G_ENT_C];

void g_ent_frame();

#include "g_zawarudo.h"

void g_ent_wryyy(struct g_zw_wryyy* wryyy);

#endif
