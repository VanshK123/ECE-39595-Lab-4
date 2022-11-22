
build:
	g++ -std=c++17 -g -o polylab poly.cc poly.h main.cpp
	./polylab

final:
	g++ -std=c++17 -Wall -Wextra -Wpedantic -Werror -O3 -o poly.cc poly.h main.cpp