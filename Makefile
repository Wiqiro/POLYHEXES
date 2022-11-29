OBJS = src/main.c src/gfx/window.c src/gfx/shaders.c src/gfx/renderer.c src/gfx/vao.c src/gfx/vbo.c src/gfx/ebo.c src/game/map.c src/game/hex.c src/game/polyhex.c src/game/game_state.c src/inputs/callbacks.c

CC = gcc

COMPILER_FLAGS = -Wall -pedantic

LINKER_FLAGS = -lGLEW -lGL -lcglm -lglfw -lm

OBJ_NAME = main

	
all: $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)

run: $(OBJS)
	./$(OBJ_NAME)

clean:
	rm -rf ./$(OBJ_NAME)