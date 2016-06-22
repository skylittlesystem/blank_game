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
#include "enderer.h"

#define WINDOW_SCALE 4
#define R_SDL_WINDOW_TITLE "!!!11!1!!1ONE!!"
#define R_SDL_WINDOW_W (WINDOW_SCALE * R_WIDTH)
#define R_SDL_WINDOW_H (WINDOW_SCALE * R_HEIGHT)

void r_moveto(struct r_enderer* R, int* p)
{
	R->p[0] = p[0];
	R->p[1] = p[1];
}

/* FIXME: */
void r_rect_fill(
		struct r_enderer* R,
		unsigned* l,
		unsigned char* c
		)
{
	SDL_Rect rect =
	{
		R->p[0],
		R->p[1],
		l[0],
		l[1]
	};

	SDL_SetRenderDrawBlendMode(R->sdl_renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(R->sdl_renderer, c[0], c[1], c[2], c[3]);
	SDL_RenderFillRect(R->sdl_renderer, &rect);
}

void r_ssheet_draw(
		struct r_enderer* R,
		unsigned id,
		unsigned i,
		unsigned j,
		unsigned char pos
		)
{
	struct r_ss_heet* ssheet = r_ssheet_get(R, id);

	SDL_Rect srcrect =
	{
		ssheet->sw * j,
		ssheet->sh * i,
		ssheet->sw,
		ssheet->sh
	};

	SDL_Rect dstrect =
	{
		R->p[0] ,
		R->p[1],
		ssheet->sw,
		ssheet->sh
	};

	if (pos == 1)
	{
		dstrect.x -= ssheet->sw/2;
		dstrect.y -= ssheet->sh/2;
	}

	else if (pos == 2)
	{
		dstrect.x -= ssheet->sw;
		dstrect.y -= ssheet->sh;
	}

	SDL_RenderCopy(
			R->sdl_renderer,
			ssheet->sdl_texture,
			&srcrect,
			&dstrect
			);
}

void r_ssanim_draw(
		struct r_enderer* R,
		unsigned id,
		unsigned long t,
		unsigned char pos
		)
{
	struct r_ss_anim* ssanim = r_ssanim_get(R, id);
	unsigned (*f)[2];

	f = ssanim->frame_v + (((R_SS_ANIM_FPS * t) / 1000) % ssanim->frame_c);
	r_ssheet_draw(R, ssanim->ssheet_id, (*f)[0], (*f)[1], pos);
}

/* FIXME: resource manager */
/* FIXME: this is leaking! no free! */
void r_ssheet_load(
		struct r_enderer* R,
		unsigned id,
		char* path
		)
{
	struct r_ss_heet* s;

	FILE* fp;
	char img_path[256];
	char txt_path[256];

	SDL_Surface* surf;
	SDL_Texture* tex;

	s = r_ssheet_get(R, id);

	assert (snprintf(img_path, sizeof (img_path), "%s/texture.png", path)
			< sizeof (img_path));

	assert (!snprintf(txt_path, sizeof (txt_path), "%s/data.txt", path)
			< sizeof (txt_path));

	surf = IMG_Load(img_path);
	assert (surf); /* TODO: handling */
	tex = SDL_CreateTextureFromSurface(R->sdl_renderer, surf);
	assert (tex); /* TODO: handling */
	SDL_FreeSurface(surf);
	s->sdl_texture = tex;

	fp = fopen(txt_path, "r");
	assert (fp); /* TODO: handling */

	fscanf(fp, "%u %u", &s->sw, &s->sh);
	s->m = surf->h / s->sh;
	s->n = surf->w / s->sw;

	fclose(fp);
}

/* FIXME: resource manager */
/* FIXME: this is leaking! no free! */
void r_ssanim_load(
		struct r_enderer* R,
		unsigned id,
		char* path,
		unsigned ssheet_id
		)
{
	struct r_ss_anim* a;

	FILE* fp;
	char a_path[256];

	unsigned i;

	a = r_ssanim_get(R, id);

	assert (snprintf(a_path, sizeof (a_path), "%s/data.txt", path)
			< sizeof (a_path));

	fp = fopen(a_path, "r");
	assert (fp); /* TODO: handling */

	a->ssheet_id = ssheet_id;

	fscanf(fp, "%u", &a->frame_c);
	a->frame_v = malloc(sizeof (*a->frame_v) * a->frame_c);

	for (i = 0; i < a->frame_c; ++i)
		fscanf(fp, "%u %u", &a->frame_v[i][0], &a->frame_v[i][1]);

	fclose(fp);
}

void r_clear(struct r_enderer* R)
{
	SDL_SetRenderDrawColor(R->sdl_renderer, 168, 230, 255, 255);
	SDL_RenderClear(R->sdl_renderer);
}

void r_present(struct r_enderer* R)
{
	SDL_RenderPresent(R->sdl_renderer);
}

void r_fini(struct r_enderer* R)
{
	SDL_DestroyRenderer(R->sdl_renderer);
	SDL_DestroyWindow(R->sdl_window);
	SDL_QuitSubSystem(SDL_INIT_VIDEO);
}

void r_init(struct r_enderer* R)
{
	memset(R, 0, sizeof (*R));

	assert(SDL_InitSubSystem(SDL_INIT_VIDEO) == 0);

	R->sdl_window = SDL_CreateWindow(
			R_SDL_WINDOW_TITLE,
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			R_SDL_WINDOW_W,
			R_SDL_WINDOW_H,
			0
			);

	assert (R->sdl_window); /* FIXME: handle */

	R->sdl_renderer = SDL_CreateRenderer(R->sdl_window, -1, 0);

	assert (R->sdl_renderer); /* FIXME: handle */

	//SDL_RenderSetScale(R->sdl_renderer, WINDOW_SCALE, WINDOW_SCALE);
	SDL_RenderSetLogicalSize(R->sdl_renderer, R_WIDTH, R_HEIGHT);
}
