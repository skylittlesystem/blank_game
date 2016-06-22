#include <assert.h>
#include <SDL.h>

#include "ixer.h"

void m_ixer_fini(struct m_ixer* mixer)
{
	Mix_Music** m;
	m = mix_get_music(mixer, 0);	
	Mix_FreeMusic(*m);

	Mix_CloseAudio();

	SDL_QuitSubSystem(SDL_INIT_AUDIO);
}

static void load_mus(struct m_ixer* mixer, unsigned id, const char* s)
{
	Mix_Music** m;
	m = mix_get_music(mixer, id);
	(*m) = Mix_LoadMUS(s);
	assert (*m);
}

void m_ixer_init(struct m_ixer* mixer)
{
	assert (SDL_Init(SDL_INIT_AUDIO) == 0);

	assert (Mix_Init(MIX_INIT_MP3));
	assert (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4*4096) == 0);

	//load_mus(mixer, 0, "data/level_clarice.mp3");
	load_mus(mixer, 0, "data/level_room.mp3");

	Mix_PlayMusic(*mix_get_music(mixer, 0), -1);


}
