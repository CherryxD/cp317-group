clean:
	rm bin/main
build:
	g++ src/main.cpp -o bin/main -Wall -g
run: build
	./bin/main
