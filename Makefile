build:
	g++ -Wall -std=c++17 -O2 src/*.cpp -lSDL2 -lm -o Renderer
run:
	./Renderer
clean:
	rm Renderer
