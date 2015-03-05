echo ===== clang++ with -Wall -Wextra ====== && clang++ -std=c++14 -stdlib=libc++ -O3 -Wall -Wextra -pedantic-errors main.cpp && ./a.out
echo ===== g++ with -Wall -Wextra ====== && g++ -std=c++14  -O3 -Wall -Wextra -pedantic-errors main.cpp && ./a.out
echo ===== clang++ without -Wall -Wextra ====== && clang++ -std=c++14 -stdlib=libc++ -O3 -pedantic-errors main.cpp && ./a.out
echo ===== g++ without -Wall -Wextra ====== && g++ -std=c++14  -O3 -pedantic-errors main.cpp && ./a.out