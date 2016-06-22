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
#include <stdio.h>

#include "awarudo.h"

unsigned char bits[] =
"################"
"##....####....##"
"##....####....##"
"##....####....##"
"##....####....##"
"##########....##"
"#####.........##"
"###...####....##"
"###...####....##"
"#####.........##"
"##########....##"
"##............##"
"######...##...##"
"######...##...##"
"########....####"
"################"
;

struct z_awarudo Z;
unsigned long teh_tiem;
bool teh_hit;

static void f(void* foo, struct z_wryyy* wryyy)
{
	teh_hit = true;
}

static void frame()
{
	z_awarudo_frame(&Z, Z_FT);
	teh_tiem += Z_FT;
}

static void test(unsigned frames)
{
	unsigned i;

	teh_hit = false;
	teh_tiem = 0;

	for (i = 0; i < frames; ++i)
	{
		assert (!teh_hit);
		frame();
	}

	assert (teh_hit);
}

static void setpixxy(
		unsigned id,
		int p0,
		int p1,
		int l0,
		int l1,
		unsigned char* bits
		)
{
	union z_jojo* a;
	a = z_jojo_get(&Z, id);

	a->type = Z_J_PIXXY;

	a->pixxy.p[0] = p0;
	a->pixxy.p[1] = p1;

	a->pixxy.l[0] = l0;
	a->pixxy.l[1] = l1;

	a->pixxy.bits = bits;
}

static void setboxxy(
		unsigned id,
		int p0,
		int p1,
		int l0,
		int l1,
		int v0,
		int v1
		)
{
	union z_jojo* a;
	a = z_jojo_get(&Z, id);

	a->type = Z_J_BOXXY;

	a->boxxy.p[0] = p0;
	a->boxxy.p[1] = p1;

	a->boxxy.l[0] = l0;
	a->boxxy.l[1] = l1;

	a->boxxy.v[0] = v0;
	a->boxxy.v[1] = v1;
}

int main(int argc, char* argv[])
{
	unsigned i;

	memset(&Z, 0, sizeof (Z));

	for (i = 0; i < sizeof (bits); ++i)
		bits[i] = (bits[i] == '#' ? 1 : 0);

	Z.on_wryyy = f;

	setpixxy(0, 0, 0, 16, 16, bits);


	setboxxy(1, 2, 1, 1, 1, -1, 0);
	test(1);

	setboxxy(1, 2, 1, 1, 1, 0, -1);
	test(1);

	setboxxy(1, 2, 1, 1, 1, -1, -1);
	test(1);

	setboxxy(1, 2, 1, 1, 1, 1, -1);
	test(1);

	setboxxy(1, 2, 1, 1, 1, -1, 1);
	test(1);

	setboxxy(1, 2, 1, 1, 1, 1, 0);
	test(4);

	setboxxy(1, 2, 1, 1, 1, 1, 1);
	test(4);

	setboxxy(1, 2, 1, 1, 1, 0, 1);
	test(4);

	setboxxy(1, 11, 2, 3, 3, 0, 1);
	test(10);

	setboxxy(1, 11, 2, 3, 3, 1, 1);
	test(1);

	setboxxy(1, 11, 2, 3, 3, -1, 1);
	test(2);

	return 0;
};
