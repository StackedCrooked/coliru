echo "This Length" >aaa.txt
echo "This Width" >>aaa.txt
echo "2.50" >> aaa.txt
# cat aaa.txt
g++ -O2 -Wall -pedantic -pthread -ansi main.cpp && ./a.out < aaa.txt