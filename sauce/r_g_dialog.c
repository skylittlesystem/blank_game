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

void r_g_dialog()
{
	unsigned i, j;

	if (g_dialog.hidden)
		return;

	r_moveto(0, R_H - R_G_DIALOG_H);
	r_ani(30, 0);

	r_translate(R_G_D_CH_W, R_G_D_CH_H);

	for (i = 0; i < G_DIALOG_H; ++i)
	{
		for (j = 0; j < G_DIALOG_W; ++j)
		{
			unsigned char* ch;
			ch = (unsigned char*) &g_dialog.text[i][j];

			SDL_Rect srcrect =
			{
				((*ch) % R_G_D_CH_N) * R_G_D_CH_W,
				((*ch) / R_G_D_CH_N) * R_G_D_CH_H,
				R_G_D_CH_W,
				R_G_D_CH_H,
			};

			r_subtex(31, &srcrect);
			r_translate(R_G_D_CH_W, 0);
		}

		r_translate(-(G_DIALOG_W * R_G_D_CH_W), R_G_D_CH_H);
	}
}
