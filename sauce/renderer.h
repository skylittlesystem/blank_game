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

#ifndef HAS_RENDERER_H
#define HAS_RENDERER_H

#define R_TITLE "blank_game"
#define R_W 320
#define R_H 240
#define R_WIN_W (4*R_W)
#define R_WIN_H (4*R_H)

#include <SDL.h>

void r_moveto(int x, int y);
void r_translate(int x, int y);
#define r_movetov(v) r_moveto(v[0], v[1])
#define r_translatev(v) r_translate(v[0], v[1])
void r_color(
		unsigned char r,
		unsigned char g,
		unsigned char b,
		unsigned char a
		);
#define r_colorv(v) r_color(v[0], v[1], v[2], v[3])
void r_clear();
void r_present();
void r_subtex(unsigned id, SDL_Rect* srcrect);
void r_tex(unsigned id);
void r_tex_load(unsigned id);
void r_tex_load_all();
void r_tex_unload(unsigned id);
void r_tex_unload_all();
void r_boxxy(SDL_Rect* r);
void r_ani(unsigned id, unsigned t);
void r_init();
void r_fini();

#endif
