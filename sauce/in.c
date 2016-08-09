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

#include <SDL.h>
#include "in.h"
#include "blank_game.h"
#include "game.h"
#include "r_game.h"

void in_frame()
{
	SDL_Event e;
	const Uint8* s;

	while (SDL_PollEvent(&e))
	{
		switch (e.type)
		{
		case SDL_KEYDOWN:
			switch (e.key.keysym.sym)
			{
			default:
				break;
			}
			break;

		case SDL_KEYUP:
			switch (e.key.keysym.sym)
			{
			case SDLK_b:
				r_g_toggle_boxxies();
				break;

			case SDLK_z:
				g_in_z();
				break;

			case SDLK_x:
				g_in_x();
				break;
			}
			break;

		case SDL_QUIT:
			main_quit();
			return;

		default:
			continue;
		}
	}

	s = SDL_GetKeyboardState(NULL);

	g_in_arrows(
		s[SDL_SCANCODE_RIGHT],
		s[SDL_SCANCODE_UP],
		s[SDL_SCANCODE_LEFT],
		s[SDL_SCANCODE_DOWN]
		);
}

void in_init()
{
}

void in_fini()
{
}
