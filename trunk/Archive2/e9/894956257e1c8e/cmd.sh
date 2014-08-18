ln -s /Archive2/d3/77462f7cb5268a/main.cpp source.utf8.txt && iconv -t utf-32 -f utf-8 source.utf8.txt -o source.utf32.txt
file source.utf32.txt
g++ -std=c++11 -Wall main.cpp && ./a.out