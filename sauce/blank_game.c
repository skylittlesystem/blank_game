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
#include <stdio.h>
#include <SDL.h>

#include "g/ame.h"
#include "w/indow.h"

static struct g_ame teh_G;
static struct w_indow teh_W;

/*
 * Teh main function!!11!1ONE
 *
 */
int main(int argc, char *argv[])
{
	unsigned long t1, t2, dt;

	g_init(&teh_G);
	w_init(&teh_W, &teh_G);

	t1 = SDL_GetTicks();
	do {
		t2 = SDL_GetTicks();
		dt = t2 - t1;

		g_frame(&teh_G, dt);
		w_frame(&teh_W, dt);

		t1 = t2;
	} while (!w_should_quit(&teh_W));

	w_fini(&teh_W);
	g_fini(&teh_G);

	SDL_Quit();

	return 0;
}
