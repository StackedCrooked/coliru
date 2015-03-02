g++ -std=c++11 -O2 -Wall -Werror -pedantic main.cpp -lboost_system
export SOCKFILE=$PWD/example.sock
./a.out $SOCKFILE &
sleep 1
echo "asio domain socket example" | nc -U $SOCKFILE