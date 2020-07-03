INC = -I$(GAIAGL)/ -I$(GAIAGL)/GaiaGL/vendor -I$(IMGUI)
LIB = -L$(GAIAGL)/GaiaGL/ -lgaiagl -lGL -lGLEW -lglfw
OBJ = $(GAIAGL)/GaiaGL/libgaiagl.a Touhou.o Parse.o State.o Menu.o DanmakuTest.o Enemy.o

NAME = Touhou
COMP = g++
FLAG = -std=c++17 -Wall #-ggdb -fsanitize=address -fno-omit-frame-pointer -fsanitize=leak

$(NAME): source.cpp $(OBJ)
	$(COMP) $^ -o $@ $(INC) $(LIB) $(FLAG)

Touhou.o: Touhou.cpp Touhou.hpp State.o Menu.o DanmakuTest.o
	$(COMP) $< -c -o $@ $(INC) $(LIB) $(FLAG)

Parse.o: Parse.cpp Parse.hpp
	$(COMP) $< -c -o $@ $(INC) $(LIB) $(FLAG)

State.o: State.cpp State.hpp
	$(COMP) $< -c -o $@ $(INC) $(LIB) $(FLAG)

Menu.o: Menu.cpp Menu.hpp State.o
	$(COMP) $< -c -o $@ $(INC) $(LIB) $(FLAG)

DanmakuTest.o: DanmakuTest.cpp DanmakuTest.hpp Parse.o Enemy.o
	$(COMP) $< -c -o $@ $(INC) $(LIB) $(FLAG)

Enemy.o: Enemy.cpp Enemy.hpp
	$(COMP) $< -c -o $@ $(INC) $(LIB) $(FLAG)

clean:
	rm *.o $(NAME)