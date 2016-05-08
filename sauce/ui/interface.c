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

#include "interface.h"

void ui_interface_poll_event(struct ui_interface* ui)
{
	SDL_Event e;

	while (SDL_PollEvent(&e))
	{
		switch (e.type)
		{
		case SDL_KEYDOWN:
		case SDL_KEYUP:
			ui_window_event(&ui->win, &e);
			break;

		case SDL_QUIT:
			ui->should_quit = true;
			return;

		default:
			continue;
		}
	}
}

void ui_interface_frame(struct ui_interface* ui, unsigned long dt)
{
	ui_interface_poll_event(ui);
	ui_window_frame(&ui->win, dt);
}

void ui_interface_fini(struct ui_interface* ui)
{
	ui_window_fini(&ui->win);
}

void ui_interface_init(struct ui_interface* ui, struct g_game* G)
{
	ui_window_init(&ui->win, G);
	ui->should_quit = false;
}
