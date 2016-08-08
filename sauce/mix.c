#include <assert.h>
#include <SDL.h>
#include <SDL_mixer.h>

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

#include "mix.h"

const char* const mus_path[MUS_C] =
{
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
};

Mix_Music* mus[MUS_C];

const char* const sfx_path[SFX_C] =
{
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
};

Mix_Chunk* sfx[SFX_C];

/* mus */
void mus_free(unsigned id)
{
	Mix_FreeMusic(mus[id]);
}

void mus_slurp(unsigned id)
{
	mus[id] = Mix_LoadMUS(mus_path[id]);

	assert (mus[id]); /* TODO: handling */
}

void mus_free_all()
{
	unsigned id;

	for (id = 0; id < MUS_C; ++id)
		mus_free(id);
}

void mus_slurp_all()
{
	unsigned id;

	for (id = 0; id < MUS_C; ++id)
		mus_slurp(id);
}

/* sfx */
void sfx_free(unsigned id)
{
	Mix_FreeChunk(sfx[id]);
}

void sfx_slurp(unsigned id)
{
	sfx[id] = Mix_LoadWAV(sfx_path[id]);

	assert (sfx[id]); /* TODO: handling */
}

void sfx_free_all()
{
	unsigned id;

	for (id = 0; id < SFX_C; ++id)
		sfx_free(id);
}

void sfx_slurp_all()
{
	unsigned id;

	for (id = 0; id < SFX_C; ++id)
		sfx_slurp(id);
}

/* mix */
void mix_init()
{
	SDL_Init(SDL_INIT_AUDIO);
	assert (Mix_Init(MIX_INIT_MP3) & MIX_INIT_MP3); /* TODO: handling */
	assert (
			Mix_OpenAudio(
				MIX_DEFAULT_FREQUENCY,
				MIX_DEFAULT_FORMAT,
				2,
				4096
				)
			== 0
	       ); /* TODO: handling */
	memset(sfx, 0, sizeof (sfx));
	memset(mus, 0, sizeof (mus));
}

void mix_fini()
{
	Mix_CloseAudio();
	Mix_Quit();
	SDL_QuitSubSystem(SDL_INIT_AUDIO);
}