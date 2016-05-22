#ifndef HAS_M_IXER_H
#define HAS_M_IXER_H

#include <SDL_mixer.h>

struct m_ixer
{
	Mix_Music* music_v[32];
};

#define mix_get_music(mixer, id) (&(mixer)->music_v[(id)])

void m_ixer_fini(struct m_ixer* mixer);
void m_ixer_init(struct m_ixer* mixer);

#endif
