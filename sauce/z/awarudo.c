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
#include <math.h>

#include "awarudo.h"

/* TODO: is this even necessary? */
static bool trace_boxxy_vs_boxxy(
		struct z_wryyy* wryyy,
		struct z_j_boxxy* sroller,
		struct z_j_boxxy* jojo
		)
{
	return 0;
}

#define max(a, b) ((a) >= (b) ? (a) : (b))
#define min(a, b) ((a) <= (b) ? (a) : (b))

#include <stdio.h>

/* TODO: perhaps Bresenham's line algorithm could be used here */
/* NOTE: If velocity is big or fps is low, collisions will be skipped. */
static bool trace_boxxy_vs_pixxy(
		struct z_wryyy* wryyy,
		struct z_j_boxxy* sroller,
		struct z_j_pixxy* jojo
		)
{
	unsigned i, j;
	int b[4], dp[2];

	dp[0] = sroller->v[0];
	dp[1] = sroller->v[1];

	b[0] = sroller->p[0] - jojo->p[0] + dp[0];
	b[1] = sroller->p[1] - jojo->p[1] + dp[1];
	b[2] = b[0] + sroller->l[0];
	b[3] = b[1] + sroller->l[1];

	b[0] = max(b[0], 0);
	b[1] = max(b[1], 0);
	b[2] = min(b[2], jojo->l[0]);
	b[3] = min(b[3], jojo->l[1]);

	for (i = b[1]; i < b[3]; ++i)
		for (j = b[0]; j < b[2]; ++j)
			if (z_j_pixxy_get_bit(jojo, i, j))
				return true;

	sroller->p[0] += dp[0];
	sroller->p[1] += dp[1];
	return false;
}

static bool trace(
		struct z_wryyy* wryyy,
		union z_jojo* sroller,
		union z_jojo* jojo
		)
{
	assert (sroller->type == Z_J_BOXXY);

	switch (jojo->type)
	{
	case Z_J_NAUGHT:
		return false;

	case Z_J_BOXXY:
		return trace_boxxy_vs_boxxy(
				wryyy,
				&sroller->boxxy,
				&jojo->boxxy
				);

	case Z_J_PIXXY:
		return trace_boxxy_vs_pixxy(
				wryyy,
				&sroller->boxxy,
				&jojo->pixxy
				);

	default:
		assert (false);
		return false;
	}
}

static inline void frame(struct z_awarudo* Z)
{
	unsigned i, j;
	union z_jojo* sroller, * jojo;
	struct z_wryyy wryyy;

	for (i = 0; i < Z_J_MAX; ++i)
	{
		sroller = z_jojo_get(Z, i);

		/* only boxxies can move */
		if (sroller->type != Z_J_BOXXY)
			continue;

		/* ignore non-moving boxxies */
		if (sroller->boxxy.v[0] == 0 && sroller->boxxy.v[1] == 0)
			continue;

		for (j = 0; j < Z_J_MAX; ++j)
		{
			memset(&wryyy, 0, sizeof (wryyy));
			wryyy.from_id = i;
			wryyy.to_id = j;

			jojo = z_jojo_get(Z, j);

			if (trace(&wryyy, sroller, jojo))
				Z->on_wryyy(Z->dio, &wryyy);
		}
	}
}

void z_awarudo_frame(struct z_awarudo* Z, unsigned long dt)
{
	Z->t_left += dt;

	while (Z_FT <= Z->t_left)
	{
		frame(Z);
		Z->t_left -= Z_FT;
	}
};
