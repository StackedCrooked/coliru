compile() { $1 -c -O2 -std=c++11 main.cpp -Wall -Wextra -Werror  -masm=intel -pedantic -S -o - | c++filt ;  }
printf "\n\n    ===  GCC  ===  \n\n"  ; compile g++
printf "\n\n    === CLANG ===  \n\n"; compile clang++