INC = -I$(GAIAGL)/ -I$(GAIAGL)/GaiaGL/vendor -I$(IMGUI) -I$(IRRKLANG)/irrKlang/include
LIB = -L$(GAIAGL)/GaiaGL/ -L$(IRRKLANG)/irrKlang/lib -lgaiagl -lGL -lGLEW -lglfw \
	$(IRRKLANG)/irrKlang/bin/linux-gcc-64/libIrrKlang.so $(IRRKLANG)/irrKlang/bin/linux-gcc-64/ikpMP3.so -pthread
OBJ = $(GAIAGL)/GaiaGL/libgaiagl.a Touhou.o State.o Menu.o DanmakuTest.o Enemy.o Spell.o Player.o

NAME = Touhou
COMP = g++
FLAG = -std=c++17 -Wall #-ggdb -fsanitize=address -fno-omit-frame-pointer -fsanitize=leak

$(NAME): source.cpp $(OBJ)
	$(COMP) $^ -o $@ $(INC) $(LIB) $(FLAG)

Touhou.o: Touhou.cpp Touhou.hpp State.o Menu.o DanmakuTest.o
	$(COMP) $< -c -o $@ $(INC) $(LIB) $(FLAG)

State.o: State.cpp State.hpp
	$(COMP) $< -c -o $@ $(INC) $(LIB) $(FLAG)

Menu.o: Menu.cpp Menu.hpp State.o
	$(COMP) $< -c -o $@ $(INC) $(LIB) $(FLAG)

DanmakuTest.o: DanmakuTest.cpp DanmakuTest.hpp Enemy.o Spell.o Player.o
	$(COMP) $< -c -o $@ $(INC) $(LIB) $(FLAG)

Enemy.o: Enemy.cpp Enemy.hpp Spell.o
	$(COMP) $< -c -o $@ $(INC) $(LIB) $(FLAG)

Spell.o: Spell.cpp Spell.hpp
	$(COMP) $< -c -o $@ $(INC) $(LIB) $(FLAG)

Player.o: Player.cpp Player.hpp
	$(COMP) $< -c -o $@ $(INC) $(LIB) $(FLAG)

clean:
	rm *.o $(NAME)