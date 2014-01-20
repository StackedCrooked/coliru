g++-4.8 -std=c++11 -Wall -Wextra -O0 -pedantic -pthread main.cpp -o a \
&& g++-4.8 -std=c++11 -Wall -Wextra -O0 -pedantic -pthread -DEXPLICIT_A_PLZ main.cpp -o b \
&& echo "original:" \
&& nm ./a | grep ZN1AIi \
&& echo "with change:" \
&& nm ./b | grep ZN1AIi