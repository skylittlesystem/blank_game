#
# TEH BLANK_GAME MAKEFIEL!!1!11ONE!
#

CC := gcc
CFLAGS := \
	-Isauce \
	`sdl2-config --cflags` \
	-std=c99 \
	-Wall \
	-pipe \
	-ggdb \
	$(CFLAGS)

LD := gcc
LDFLAGS := \
	-lm \
	`sdl2-config --libs` \
	-lSDL2_image \
	-lSDL2_mixer \
	$(LDFLAGS)

LD := $(LD)

OBJ := \
	build/r/enderer.o \
	build/r/game.o \
	build/m/ixer.o \
	build/ui/interface.o \
	build/ui/window.o \
	build/g/ame.o \
	build/misc/sblas3.o \
	build/blank_game.o \

PRG := \
	build/blank_game \

.PHONY: all clean

all: $(PRG)

clean:
	rm -f $(OBJ) $(PRG)

build/%.o: sauce/%.c
	mkdir -p `dirname $@`
	$(CC) $(CFLAGS) -o $@ -c $<

$(PRG): $(OBJ)
	mkdir -p `dirname $@`
	$(LD) $(LDFLAGS) -o $@ $^
