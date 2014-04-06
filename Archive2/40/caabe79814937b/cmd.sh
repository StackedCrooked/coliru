g++-4.8 -std=c++03 -O2 -Wall -pedantic -pthread main.cpp &&
g++-4.8 -std=c++11 -DHAS_CPLUSPLUS11 -O2 -Wall -pedantic -pthread main.cpp;