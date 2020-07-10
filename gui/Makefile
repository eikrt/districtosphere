OBJS = gui.c gui.h ../file/file.c ../file/file.h ../io/imgload.c ../io/imgload.h

CC = gcc

COMPILER_FLAGS = -w

LINKER_FLAGS = -lSDL2 -lm

OBJ_NAME = application

all : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
