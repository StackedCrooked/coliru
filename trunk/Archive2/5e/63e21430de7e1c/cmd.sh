cat <<HERE > input.txt; clang++ -std=c++11 -Os main.cpp -lpthread && ./a.out input.txt
<some text with nested <tags <etc...> >more text>
HERE