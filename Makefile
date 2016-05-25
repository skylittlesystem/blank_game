#
# TEH BLANK_GAME MAKEFIEL!!1!11ONE!
#

CC := gcc
CFLAGS := \
	-Isauce \
	`pkg-config sdl2 --cflags` \
	`pkg-config SDL2_image --cflags` \
	`pkg-config SDL2_mixer --cflags` \
	-std=c99 \
	-Wall \
	-pipe \
	-ggdb \
	$(CFLAGS)

LD := gcc
LDFLAGS := \
	-lm \
	`pkg-config sdl2 --libs` \
	`pkg-config SDL2_image --libs` \
	`pkg-config SDL2_mixer --libs` \
	$(LDFLAGS)

LD := $(LD)

OBJ := \
	build/r/enderer.o \
	build/m/ixer.o \
	build/w/indow.o \
	build/w/draw.o \
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
