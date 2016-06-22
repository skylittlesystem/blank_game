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

#ifndef W_INDOW_H
#define W_INDOW_H

#include <stdbool.h>
#include "r/enderer.h"
#include "m/ixer.h"
#include "g/ame.h"

struct w_indow
{
	struct r_enderer R;
	struct m_ixer M;
	struct g_ame* G;
};

enum
{
	W_SSHEET_AILIN,
	W_SSHEET_PACSATAN,
	W_SSHEET_LEVEL_CLARICE,
	W_SSHEET_LEVEL_LABYRINTH,
};

enum
{
	W_SSANIM_AILIN_MONGOL,
	W_SSANIM_PACSATAN_NHAC,
};

#define w_should_quit(W) ((W)->G->gameover)

void w_frame(struct w_indow* W, unsigned long dt);
void w_fini(struct w_indow* W);
void w_init(struct w_indow* W, struct g_ame* G);

#endif
