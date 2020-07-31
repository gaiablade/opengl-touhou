INC = -I$(HOME)/github/GaiaGL/ -I$(HOME)/github/GaiaGL/vendor -I$(IMGUI) -I$(IRRKLANG)/irrKlang/include
LIB = -L$(GAIAGL)/GaiaGL/ -L$(IRRKLANG)/irrKlang/lib -lgaiagl -lGL -lGLEW -lglfw \
	$(IRRKLANG)/irrKlang/bin/linux-gcc-64/libIrrKlang.so $(IRRKLANG)/irrKlang/bin/linux-gcc-64/ikpMP3.so -pthread \
	-L$(HOME)/assimp/code -lassimp
OBJ = Touhou.o State.o Menu.o \
	Enemy.o Spell.o Player.o EditSpell.o

NAME = Touhou
COMP = g++
FLAG = -std=c++2a -Wall #-ggdb -fsanitize=address -fno-omit-frame-pointer -fsanitize=leak

all: source.cpp $(OBJ) pch.h.gch
	$(COMP) source.cpp $(HOME)/github/GaiaGL/GaiaGL/libgaiagl.a $(OBJ) -o $(NAME) $(INC) $(LIB) $(FLAG)

Touhou.o: Touhou.cpp Touhou.hpp State.o Menu.o EditSpell.o #DanmakuTest.o EditSpell.o
	$(COMP) $< -c -o $@ $(INC) $(LIB) $(FLAG)

State.o: State.cpp State.hpp
	$(COMP) $< -c -o $@ $(INC) $(LIB) $(FLAG)

Menu.o: Menu.cpp Menu.hpp State.o
	$(COMP) $< -c -o $@ $(INC) $(LIB) $(FLAG)

DanmakuTest.o: DanmakuTest.cpp DanmakuTest.hpp Enemy.o Spell.o Player.o
	$(COMP) $< -c -o $@ $(INC) $(LIB) $(FLAG)

EditSpell.o: EditSpell.cpp EditSpell.hpp Spell.o
	$(COMP) $< -c -o $@ $(INC) $(LIB) $(FLAG)

Enemy.o: Enemy.cpp Enemy.hpp Spell.o
	$(COMP) $< -c -o $@ $(INC) $(LIB) $(FLAG)

Spell.o: Spell.cpp Spell.hpp
	$(COMP) $< -c -o $@ $(INC) $(LIB) $(FLAG)

Player.o: Player.cpp Player.hpp
	$(COMP) $< -c -o $@ $(INC) $(LIB) $(FLAG)

pch.h.gch: pch.h
	$(COMP) -c $^ -o $@

clean:
	rm *.o $(NAME)