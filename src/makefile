CC = g++ -g
CFLAGS = `sdl-config --cflags` -O3
LDFLAGS = `sdl-config --libs` -lSDL_image -lGL -lSDL_mixer

exec = ../vector_space
headers = $(wildcard *.h)
sources = $(wildcard *.cpp)
objects = $(sources:%.cpp=../build/%.o)

all: $(exec)

$(exec): $(objects)
	$(CC) -o $(exec) $(objects) $(CFLAGS) $(LDFLAGS) 

../build/%.o: %.cpp $(headers)
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -f $(objects) $(exec) *~
