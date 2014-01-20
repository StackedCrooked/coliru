g++-4.8 -std=c++11 -Wall -Wextra -O0 -pedantic -pthread main.cpp -o a \
&& g++-4.8 -std=c++11 -Wall -Wextra -O3 -pedantic -pthread -DEXPLICIT_A_PLZ main.cpp -o b \
&& nm ./a | grep ZN1AIi > a-symbols \
&& nm ./b | grep ZN1AIi > b-symbols \
&& diff --side-by-side a-symbols b-symbols