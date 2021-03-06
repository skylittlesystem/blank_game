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

#ifndef HAS_IMG_H
#define HAS_IMG_H

#include <SDL.h>

#include "id_2_path.h"

#define IMG_C 32
extern const char* const img_id_2_path_path;
extern char img_id_2_path[IMG_C][ID_2_PATH_LEN];
extern const char* const img_path[IMG_C];
extern SDL_Surface* img[IMG_C];

#define img_id_2_path_slurp() \
	id_2_path_slurp(img_id_2_path_path, ANI_C, img_id_2_path[0])

void img_free(unsigned i);
void img_slurp(unsigned i);
void img_free_all();
void img_slurp_all();
void img_init();
void img_fini();

#endif
