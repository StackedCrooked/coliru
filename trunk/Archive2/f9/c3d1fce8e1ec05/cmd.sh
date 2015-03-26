g++ -std=c++11 -O2 -Wall -Werror -pedantic main.cpp -pthread -lboost_system
./a.out &
PID=$!
sleep 2
kill -s SIGUSR1 $PID