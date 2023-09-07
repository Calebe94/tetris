##
# Tetris Game
#
# @file
# @version 0.1

CC=g++
TITLE=tetris
SOURCE=$(wildcard src/*.cpp)
SDL2_FLAGS=`$$(which sdl2-config) --cflags --libs`
INCLUDE_PATH=-Isrc/
INCLUDE_PATH+=-Ilib/seethe/
FLAGS=-Wall -Wextra
# FLAGS+=-fanalyzer
LIBS='-Wl,-rpath,$$ORIGIN' $(SDL2_FLAGS) -l SDL2_image -l SDL2_mixer -l SDL2_ttf ${INCLUDE_PATH}

MACROS=-DLOG_LEVEL=INFO

OUTPUT_DIR=bin/
BIN=bin/${TITLE}

${OUTPUT_DIR}:
	@mkdir -p ${OUTPUT_DIR}

compile: ${OUTPUT_DIR}
	@$(CC) $(FLAGS) $(SOURCE) $(LIBS) -o $(BIN) $(MACROS)

run: compile
	$(BIN)

all: compile

clean:
	rm -fr ${OUTPUT_DIR}

.PHONY: ${OUTPUT_DIR} compile clean
# end
