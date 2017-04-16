OUT = sdlmove
CXX = g++
SDL = -lSDLmain -lSDL -lSDL_image -lsfmt

OBJECTS = sdlmove.o

sources = sdlmove.cpp

all: $(OUT)

$(OUT): $(OBJECTS)
		$(CXX) ${SDL} -o $(OUT) $(OBJECTS)

OBJECTS = sdlmove.cpp
