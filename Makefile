#
# TEH BLANK_GAME MAKEFIEL!!1!11ONE!
#

CC := gcc
LD := gcc
CFLAGS := -std=c99 -Wall -pipe -ggdb
LDFLAGS := -lm

SDL2_CFLAGS := `sdl2-config --cflags`
SDL2_LIBS := `sdl2-config --libs` -lSDL2_image -lSDL2_mixer

CFLAGS := -Isauce -Ibuild/renderer/shaders $(SDL2_CFLAGS) $(CFLAGS)
LDFLAGS := $(SDL2_LIBS) $(LDFLAGS)

CC := $(CC) $(CFLAGS)
LD := $(LD) $(LDFLAGS)

#
# 3rd party lib objects
#

#
# engine objects
#
OBJ := \
	build/r/renderer.o \
	build/r/game.o \
	build/mix/er.o \
	build/ui/interface.o \
	build/ui/window.o \
	build/g/game.o \
	build/blank_game.o \

#
# programs
#

PRG := \
	build/blank_game \

#
# targets
#

build/%.o: sauce/%.c
	mkdir -p `dirname $@`
	$(CC) -o $@ -c $<

$(PRG): $(OBJ)
	mkdir -p `dirname $@`
	$(LD) -o $@ $^

.PHONY: all clean

clean:
	rm -f $(OBJ) $(PRG)

all: $(PRG)
