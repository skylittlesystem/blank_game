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

#include <stdbool.h>

enum z_j_type
{
	Z_J_NAUGHT = 0,
	Z_J_BOXXY,
	Z_J_PIXXY,
};

struct z_j_boxxy
{
	enum z_j_type type;
	int p[2];
	unsigned l[2];
	int v[2];
};

struct z_j_pixxy
{
	enum z_j_type type;
	int p[2];
	unsigned l[2];
	unsigned char* bits;
};

#define z_j_pixxy_get_bit(p, i, j) ((p)->bits[(p)->l[0] * (i) + (j)])

union z_jojo
{
	enum z_j_type type;
	struct z_j_boxxy boxxy;
	struct z_j_pixxy pixxy;
};

struct z_wryyy
{
	unsigned from_id;
	unsigned to_id;
	unsigned long dt;
};

#define Z_J_MAX 32
#define Z_FPS 25
#define Z_FT (1000/Z_FPS)

struct z_awarudo
{
	unsigned t_left;
	union z_jojo jojo_v[Z_J_MAX];
	void* dio;
	void (*on_wryyy)(void*, struct z_wryyy*);
};

#define z_jojo_get(Z, id) (&(Z)->jojo_v[(id)])

void z_awarudo_frame(struct z_awarudo* Z, unsigned long dt);
