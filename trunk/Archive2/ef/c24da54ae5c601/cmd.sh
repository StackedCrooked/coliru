cat <<HERE > input.txt; clang++ -std=c++11 -O3 main.cpp -lpthread -lboost_chrono -lboost_system && ./a.out input.txt
<some text with nested <tags <etc...> >more text>
HERE