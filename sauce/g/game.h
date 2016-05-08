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

#ifndef HAS_G_GAME_H
#define HAS_G_GAME_H

#define G_MAX_ENTITIES 16

enum g_type
{
	G_NAUGHT = 0,
	G_AILIN,
	G_WALL,
};

struct g_entity
{
	enum g_type type;
	float pos[2];
	float vel[2];
};

struct g_game
{
	unsigned state;
	struct g_entity entity_v[G_MAX_ENTITIES];
};

#define g_get_entity(G, id) (&(G)->entity_v[(id)])
#define g_get_player_entity(G) g_get_entity((G), 0)

void g_game_frame(struct g_game* G, unsigned long dt);
void g_game_fini(struct g_game* G);
void g_game_init(struct g_game* G);

#endif
