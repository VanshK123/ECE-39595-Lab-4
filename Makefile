
build:
	g++ -std=c++17 -g -o polylab poly.hpp poly.h main.cpp

final:
	g++ -std=c++17 -Wall -Wextra -Wpedantic -Werror -O3 -o poly.hpp poly.h main.cpp