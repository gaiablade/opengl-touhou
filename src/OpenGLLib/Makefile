EXEC = OpenGL.a
COMP = g++
LIB = -lglfw -lGLEW -lGL
FLAGS = -Wall
DIRS = -I./ -Ivendor/
OBJS = Graphics/*.o Input/*.o

$(EXEC): $(OBJS)
	ar rvs $@ $(OBJS)

# Remove .o Files
clean:
	rm *.o
