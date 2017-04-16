OUT = sdltest
CXX = g++
SDL = -lSDLmain -lSDL -lSDL_image -lsfmt

OBJECTS = sdltest.o

sources = sdltest.cpp

all: $(OUT)

$(OUT): $(OBJECTS)
		$(CXX) ${SDL} -o $(OUT) $(OBJECTS)

OBJECTS = sdltest.cpp
