#OBJS specifies which files to compile as part of the project
#OBJS = main.c map.c polyomino.c
OBJS = src/main.c src/gfx/window.c src/gfx/shaders.c src/gfx/renderer.c src/gfx/vao.c src/gfx/vbo.c src/gfx/ebo.c src/game/map.c src/game/hex.c src/game/polyhex.c src/game/game_state.x

#CC specifies which compiler we're using
CC = gcc

#INCLUDE_PATHS specifies the additional include paths we'll need
INCLUDE_PATHS = -I./libs

#LIBRARY_PATHS specifies the additional library paths we'll need
LIBRARY_PATHS = -L./bin

#COMPILER_FLAGS specifies the additional compilation options we're using
COMPILER_FLAGS = -Wall -Werror -pedantic #-Wl,-subsystem,windows

#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = -lglew32 -lglfw3 -lopengl32 -lgdi32

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = main

#This is the target that compiles our executable
all : $(OBJS)
	$(CC) $(OBJS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
	export.bat ${OBJ_NAME}