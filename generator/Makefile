OBJS = generator.c generator.h ../file/file.c ../file/file.h ../world/planet.h ../world/entity.h ../world/point.h

CC = gcc

COMPILER_FLAGS = -w

LINKER_FLAGS = -lm

OBJ_NAME = application

all : $(OBJS)
	$(CC) $(OBJS) $(LINKER_FLAGS) -o $(OBJ_NAME)
