g++ -std=c++11 -Wall -Wextra -Werror -pedantic-errors -ggdb3 main.cpp -o encode && cp encode decode

echo "a, b, c" >aa
./encode "$(cat aa)" | tee -a a ; mv a aa
./encode "$(cat aa)" | tee -a a ; mv a aa
./encode "$(cat aa)" | tee -a a ; mv a aa
./encode "$(cat aa)" | tee -a a ; mv a aa
./encode "$(cat aa)" | tee -a a ; mv a aa
./encode "$(cat aa)" | tee -a a ; mv a aa