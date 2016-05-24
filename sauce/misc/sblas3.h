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

#ifndef HAS_SBLAS3_H
#define HAS_SBLAS3_H

#include <stdbool.h>

typedef float vec;

vec dot3(const vec* restrict x, const vec* restrict y);
void axpy3(vec alpha, const vec* restrict x, vec* restrict y);
void scal3(vec alpha, vec* restrict x);
void gemv3(
		bool trans,
		vec alpha,
		const vec* restrict A,
		const vec* restrict x,
		vec beta,
		vec* restrict y
	    );

void gemm3(
		bool transA,
		bool transB,
		vec alpha,
		const vec* restrict A,
		const vec* restrict B,
		vec beta,
		vec* restrict C
	  );

#endif
