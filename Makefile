LIBS = -lSDL2main -lSDL2 -lSDL2_image -lsfmt
CFLAGS = -Wall

OBJS = $($SRC:.cpp=.o)

SRC = sdlmitsu.cpp

sdlmitsu: sdlmitsu.cpp
		g++ -o $@ $^ $(CFLAGS) $(LIBS)
