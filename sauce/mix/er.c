#include <assert.h>
#include <SDL.h>

#include "er.h"

void mix_er_fini(struct mix_er* mixer)
{
	Mix_Music** m;
	m = mix_get_music(mixer, 0);	
	Mix_FreeMusic(*m);

	Mix_CloseAudio();

	SDL_QuitSubSystem(SDL_INIT_AUDIO);
}

static void load_mus(struct mix_er* mixer, unsigned id, const char* s)
{
	Mix_Music** m;
	m = mix_get_music(mixer, id);
	(*m) = Mix_LoadMUS(s);
	assert (*m);
}

void mix_er_init(struct mix_er* mixer)
{
	assert (SDL_Init(SDL_INIT_AUDIO) == 0);

	assert (Mix_Init(MIX_INIT_MP3));
	assert (Mix_OpenAudio(48000, MIX_DEFAULT_FORMAT, 2, 4*4096) == 0);

	load_mus(mixer, 0, "data/level_clarice.mp3");

	Mix_PlayMusic(*mix_get_music(mixer, 0), -1);


}
