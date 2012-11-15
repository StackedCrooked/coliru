OPTIONS=-std=c++0x -Wall -Wextra -Werror -pedantic-errors -isystem /usr/local/include -isystem /usr/include
all:
	g++ -o sandbox ${OPTIONS} main.cpp
	g++ -o testapp ${OPTIONS} testapp.cpp
	./sandbox ./testapp
