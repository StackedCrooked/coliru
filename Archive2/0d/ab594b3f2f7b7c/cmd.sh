echo clang++ && clang++ -std=c++11 -stdlib=libc++ -O2 -Wall -Wextra -pedantic-errors -c main.cpp
echo g++ && g++-4.9 -std=c++11 -O2 -Wall -Wextra -pedantic-errors -c main.cpp
echo 'clang++ c++1y' && clang++ -std=c++1y -stdlib=libc++ -O2 -Wall -Wextra -pedantic-errors -c main.cpp
echo 'g++ c++1y' && g++-4.9 -std=c++1y -O2 -Wall -Wextra -pedantic-errors -c main.cpp