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

#include "renderer.h"
#include "g_dialog.h"
#include "r_g_dialog.h"
#include "ani.h"

/* FIXME: this file is so lame */

void r_g_dialog()
{
	struct ani* boxxy, * font;
	unsigned i, j;
	int p[2];

	if (g_dialog.hidden)
		return;

	boxxy = &ani[30];
	font = &ani[31];

	p[0] = 0;
	p[1] = R_H - boxxy->f_h;

	r_movetov(p);
	r_ani(30, 0);

	p[0] += font->f_w;
	p[1] += font->f_h;

	for (i = 0; i < G_DIALOG_H; ++i)
	{
		for (j = 0; j < G_DIALOG_W; ++j)
		{
			r_moveto(p[0] + (j * font->f_w), p[1] + (i * font->f_h));	
			r_ani(31, g_dialog.text[i][j]);
		}
	}
	
	
}
