#title boost asio handle allocation with asio_handler_allocate and asio_handler_deallocate
g++ -std=c++11 -O2 -Wall -pedantic -pthread main.cpp -lboost_system -lboost_thread && ./a.out