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

#ifndef HAS_GAME_H
#define HAS_GAME_H

#include <stdbool.h>
#include <SDL.h>

enum g_ent_type
{
	G_ENT_NAUGHT = 0,
	G_ENT_AILIN,
	G_ENT_PACSATAN,
	G_ENT_LEVEL_CLARICE,
	G_ENT_LEVEL_LABYRINTH,
	G_ENT_LEVEL_ROOM,
	G_ENT_TYPE_C
};

struct g_ent
{
	enum g_ent_type type;
	SDL_Rect boxxy;
	int v[2];
	unsigned bmp_id;
};

struct g_lvl
{
	char miau;
};

struct game
{
	unsigned lvl_id;
};

extern unsigned long g_t, g_dt;

#define G_C 3
#define G_LVL_C 8
#define G_ENT_C 32

extern char* const const g_path_fmt;
extern const char* const g_lvl_path_fmt[G_LVL_C];

extern unsigned g_id;
extern struct game game;

extern unsigned g_lvl_id;
extern struct g_lvl g_lvl;

extern struct g_ent g_ent[G_ENT_C];


/* ent */

/* lvl */
//static const char* g_lvl_path(unsigned id);
//static void g_lvl_slurp(unsigned id);
void g_lvl_load(unsigned id);

/* game */
void g_in_arrows(bool r, bool u, bool l, bool d);
void g_in_x();
void g_in_z();

//static void g_tick();
void g_frame();
//static const char* g_path(unsigned id);
//static void g_slurp(unsigned id);
void g_load(unsigned id);
void g_quit();
void g_init();
void g_fini();

#endif
