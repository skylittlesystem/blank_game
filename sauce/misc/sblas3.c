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

#include "sblas3.h"

vec dot3(vec* restrict x, vec* restrict y)
{
	register unsigned i;
	register vec dot = 0;

	for (i = 0; i < 3; ++i)
		dot += x[i] * y[i];

	return dot;
}

void axpy3(vec alpha, vec* restrict x, vec* restrict y)
{
	register unsigned i;

	for (i = 0; i < 3; ++i)
		y[i] += alpha * x[i];
}

void scal3(vec alpha, vec* restrict x)
{
	register unsigned i;

	for (i = 0; i < 3; ++i)
		x[i] *= alpha;
}

void gemv3(
		vec alpha,
		vec* restrict A,
		vec* restrict x,
		vec beta,
		vec* restrict y
	    )
{
	register unsigned i, j;

	for (i = 0; i < 3; ++i)
	{
		y[i] = beta * y[i];
		for (j = 0; j < 3; ++j)
			y[i] += alpha * A[i + 3 * j] * x[j];
	}
}
