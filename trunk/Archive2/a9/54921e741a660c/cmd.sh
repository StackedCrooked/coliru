g++ -std=c++11 -Wall -Wextra -Werror -pedantic-errors -ggdb3 main.cpp -o encode && cp encode decode

printf "\n     ****************** ENCODE ******************\n\n"
./encode "$(cat main.cpp)" | tee -a enc

printf "\n     ****************** DECODE ******************\n\n"
./decode "$(cat enc)"