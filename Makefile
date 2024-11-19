clean:
	rm bin/main
build:
	g++ src/main.cpp -o bin/main -Wall -g
run: build
	./bin/main bin/CourseFile.txt bin/NameFile.txt bin/OutputFile.txt
