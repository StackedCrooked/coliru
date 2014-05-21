cat<<HERE>input.txt; clang++ -std=c++11 -Os -Wall -pedantic -pthread main.cpp -lboost_system -lboost_program_options && ./a.out
[PLAYERDATA]
NAME = Game1A_g
ID = 12231
GDIFF = Medium
#Difficulty Values

[EASY]
ERAND = 0.25f
PDMOD = 2.12f
CDMOD = 0.65f
IRL = 1
IRH = 10

[MEDIUM]
ERAND = 1.00f
PDMOD = 1.00f
CDMOD = 1.00f
IRL = 1
IRH = 25

[HARD]
ERAND = 1.35f
PDMOD = 0.75f
CDMOD = 1.50f
IRL = 1
IRH = 30

HERE