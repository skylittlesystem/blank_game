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

#include "in.h"
#include "game.h"
#include "renderer.h"
#include "r_game.h"
#include "mix.h"
#include "mix_game.h"

#include "img.h"
#include "ani.h"

bool run = true;

void main_quit()
{
	run = false;
}

/* Teh main function!!11!1ONE */
int main(int argc, char *argv[])
{
	img_slurp_all();
	ani_slurp_all();

	g_init();
	in_init();

	r_init();
	r_tex_load_all();

	mix_init();
	mix_g_init();
	mus_slurp_all();

	g_load(0);

	run = true;
	while (run && !game.should_quit)
	{
		in_frame();
		g_frame();
		mix_g_frame();
		r_color(169, 231, 255, 1);
		r_clear();
		r_game();
		r_present();
	}

	mix_g_fini();
	mix_fini();
	r_fini();
	in_fini();
	g_fini();

	/* TODO: teh modules only SDL_QuitSubSystem */
	SDL_Quit();

	return 0;
}
