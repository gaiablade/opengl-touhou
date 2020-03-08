EXEC = Touhou
COMP = g++
LIB = -lglfw -lGLEW -lGL
FLAGS = -Wall
DIRS = -I./OpenGLLib/ -IOpenGLLib/vendor/ -LOpenGLLib/ -LOpenGLLib/vendor/ -IOpenGLLib/Graphics

$(EXEC): source.cpp Player.o Laser.o GameManager.o OpenGLLib/OpenGL.a
	$(COMP) $^ -o $(EXEC) $(LIB) $(FLAGS) $(DIRS)

Player.o: Player.cpp Player.h
	$(COMP) $< -c $(FLAGS) $(DIRS)

Laser.o: Laser.cpp Laser.h
	$(COMP) $< -c $(FLAGS) $(DIRS)

GameManager.o: GameManager.cpp GameManager.h Player.o
	$(COMP) $< -c $(FLAGS) $(DIRS)

# Remove .o Files
clean:
	rm *.o
