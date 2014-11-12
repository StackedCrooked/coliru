echo '---------- clang++ libc++ --------------'
clang++ -std=c++11 -stdlib=libc++ -O2 -Wall -Wextra -pedantic-errors main.cpp -lsupc++ && echo '*** ok ***'
echo -e '\n---------- g++ libstdc++ ------------' 
g++-4.8 -std=c++11 -O2 -Wall -Wextra -pedantic-errors main.cpp && echo '*** ok ***'