COMP = g++
LIB = -lglfw -lGLEW -lGL
FLAGS = -Wall
DIRS = -I../ -I../vendor/
API = DirectionalComponent.o
OBJS = $(API)

all: $(OBJS)

DirectionalComponent.o: DirectionalComponent.cpp DirectionalComponent.h
	$(COMP) $< -c $(DIRS) $(FLAGS)

# Remove .o Files
clean:
	rm *.o
