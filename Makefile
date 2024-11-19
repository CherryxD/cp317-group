clean:
	rm bin/calcgrades
build:
	g++ src/main.cpp -o bin/calcgrades -Wall -g
run: build
	./bin/calcgrades bin/CourseFile.txt bin/NameFile.txt bin/OutputFile.txt
