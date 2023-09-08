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
DEAR_IMGUI_DIR=lib/imgui/
INCLUDE_PATH+=-I${DEAR_IMGUI_DIR}
INCLUDE_PATH+=-I${DEAR_IMGUI_DIR}/backends/
DEAR_IMGUI_SOURCES=$(wildcard ${DEAR_IMGUI_DIR}*.cpp)
DEAR_IMGUI_SOURCES+=${DEAR_IMGUI_DIR}backends/imgui_impl_sdl2.cpp
DEAR_IMGUI_SOURCES+=${DEAR_IMGUI_DIR}backends/imgui_impl_sdlrenderer2.cpp
FLAGS=-Wall -Wextra
# FLAGS+=-fanalyzer
LIBS='-Wl,-rpath,$$ORIGIN' $(SDL2_FLAGS) -lSDL2_image -lSDL2_mixer -lSDL2_ttf ${INCLUDE_PATH}

# Add Dear ImGui objects to SOURCE
SOURCE+=$(DEAR_IMGUI_SOURCES)

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
