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

#ifndef HAS_MIX_H
#define HAS_MIX_H

#include <SDL_mixer.h>
#include "id_2_path.h"

#define MIX_HZ 44100

#define MUS_C 8
extern const char* const mus_id_2_path_path;
extern char mus_id_2_path[MUS_C][ID_2_PATH_LEN];
extern Mix_Music* mus[MUS_C];

#define mus_id_2_path_slurp() \
	id_2_path_slurp(mus_id_2_path_path, ANI_C, mus_id_2_path[0])

#define SFX_C 8
extern const char* const sfx_id_2_path_path;
extern char sfx_id_2_path[SFX_C][ID_2_PATH_LEN];
extern Mix_Chunk* sfx[SFX_C];

#define sfx_id_2_path_slurp() \
	id_2_path_slurp(sfx_id_2_path_path, ANI_C, sfx_id_2_path[0])

/* mus */
void mus_play(unsigned i);
void mus_free(unsigned i);
void mus_slurp(unsigned i);
void mus_free_all();
void mus_slurp_all();

/* sfx */
void sfx_free(unsigned i);
void sfx_slurp(unsigned i);
void sfx_free_all();
void sfx_slurp_all();

/* mix */
void mix_init();
void mix_fini();

#endif
