OBJS = gui.c gui.h ../file/file.c ../file/file.h ../io/imgload.c ../io/imgload.h ../utilities/camera.h ../collision/collision.c ../collision/collision.h ../world/point.h

CC = gcc

COMPILER_FLAGS = -w -g

LINKER_FLAGS = -lSDL2 -lm -lSDL2_ttf

OBJ_NAME = application

all : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
