CPP_FILES := $(wildcard src/*.cpp)
OBJ_FILES := $(addprefix obj/,$(notdir $(CPP_FILES:.cpp=.o)))
CC_FLAGS := -Wall -Werror -ansi -pedantic

all: rshell

rshell: $(OBJ_FILES)
	mkdir -p bin
	g++ -o bin/$@ $^

obj/%.o: src/%.cpp
	mkdir -p obj
	g++ $(CC_FLAGS) -c -o $@ $<

clean:
	rm -r bin obj
