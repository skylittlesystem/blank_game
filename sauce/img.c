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
#include <SDL_image.h>

#include "img.h"

const char* const img_path[IMG_C] =
{
	"data/img/naught.png",
	"data/ani/ailin/ailin.png",
	"data/ani/pacsatan/pacsatan.png",
	"data/img/level_clarice.png",
	"data/img/level_labyrinth.png",
	NULL,
	NULL,
	NULL,
};

SDL_Surface* img[IMG_C];

void img_free(unsigned id)
{
	SDL_FreeSurface(img[id]);
}

void img_slurp(unsigned id)
{
	if (!img_path[id])
		return;

	img[id] = IMG_Load(img_path[id]);
	assert (img[id]); /* TODO: handling */
}

void img_free_all()
{
	unsigned id;

	for (id = 0; id < IMG_C; ++id)
		img_free(id);
}

void img_slurp_all()
{
	unsigned id;

	for (id = 0; id < IMG_C; ++id)
		img_slurp(id);
}

void img_init()
{
	assert (IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG); /* TODO: handling */
	memset(img, 0, sizeof (img));
}

void img_fini()
{
	IMG_Quit();
}
