#ifndef HAS_MIX_ER_H
#define HAS_MIX_ER_H

#include <SDL_mixer.h>

struct mix_er
{
	Mix_Music* music_v[32];
};

#define mix_get_music(mixer, id) (&(mixer)->music_v[(id)])

void mix_er_fini(struct mix_er* mixer);
void mix_er_init(struct mix_er* mixer);

#endif
