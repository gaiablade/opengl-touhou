EXEC = Touhou
COMP = g++
LIB = -lglfw -lGLEW -lGL
FLAGS = -Wall
DIRS = -I./GaiaGL/ -IGaiaGL/vendor/ -LGaiaGL/ -LGaiaGL/vendor/ -IGaiaGL/Graphics

$(EXEC): source.cpp Player.o Enemy.o Laser.o GameManager.o Entity.o GaiaGL/GaiaGL.a
	$(COMP) $^ -o $(EXEC) $(LIB) $(FLAGS) $(DIRS)

Player.o: Player.cpp Player.h Entity.o
	$(COMP) $< -c $(FLAGS) $(DIRS)

Enemy.o: Enemy.cpp Enemy.h Entity.o
	$(COMP) $< -c $(FLAGS) $(DIRS)

Entity.o: Entity.cpp Entity.h
	$(COMP) $< -c $(FLAGS) $(DIRS)

Laser.o: Laser.cpp Laser.h
	$(COMP) $< -c $(FLAGS) $(DIRS)

GameManager.o: GameManager.cpp GameManager.h Player.o Enemy.o
	$(COMP) $< -c $(FLAGS) $(DIRS)

# Remove .o Files
clean:
	rm *.o
