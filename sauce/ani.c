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
#include "ani.h"

const char* const ani_path[ANI_C] =
{
	"data/ani/naught/naught.txt",
	"data/ani/ailin/ailin.txt",
	"data/ani/pacsatan/pacsatan.txt",
	"data/ani/level_clarice/level_clarice.txt",
	"data/ani/level_labyrinth/level_labyrinth.txt",
	NULL,
	NULL,
	NULL,
};

struct ani ani[ANI_C];

void ani_slurp(unsigned id)
{
	int r;
	FILE* fp;
	struct ani* a;
	struct ani_frm* f;
	unsigned i, lastt;

	if (!ani_path[id])
		return;

	fp = fopen(ani_path[id], "rb");
	assert (fp); /* TODO: handling  */

	a = &ani[id];
	r = fscanf(
			fp,
			" %u %d %d %u %u %u ",
			&a->tex_id,
			&a->x,
			&a->y,
			&a->f_w,
			&a->f_h,
			&a->c
		  );

	assert (r == 6); /* TODO: handling */

	lastt = 0;
	for (i = 0, f = a->v; i < a->c; ++i, ++f)
	{
		r = fscanf(
				fp,
				" %u %hhu %hhu %hu ",
				&f->t,
				&f->i,
				&f->j,
				&f->sfx_id
			  );

		assert (r == 4); /* TODO: handling */
		assert (lastt <= f->t); /* just in case =O3 */
		lastt = f->t;
	}

	assert (a->v[0].t == 0); /* just in case =O3(2) */

	fclose(fp);
}

void ani_slurp_all()
{
	unsigned id;

	for (id = 0; id < ANI_C; ++id)
		ani_slurp(id);
}
