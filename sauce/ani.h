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

#ifndef HAS_ANI_H
#define HAS_ANI_H

#define ANI_FRM_C 256
#define ANI_C 32

#include "id_2_path.h"

struct ani_frm
{
	unsigned t;
	unsigned char i;
	unsigned char j;
	unsigned short sfx_id;
};

struct ani
{
	unsigned tex_id;
	int x;
	int y;
	unsigned f_w;
	unsigned f_h;
	unsigned c;
	struct ani_frm v[ANI_FRM_C];
};

extern const char* const ani_id_2_path_path;
extern char ani_id_2_path[ANI_C][ID_2_PATH_LEN];
extern struct ani ani[ANI_C];

#define ani_id_2_path_slurp() \
	id_2_path_slurp(ani_id_2_path_path, ANI_C, ani_id_2_path[0])

void ani_slurp(unsigned id);
void ani_slurp_all();

#endif
