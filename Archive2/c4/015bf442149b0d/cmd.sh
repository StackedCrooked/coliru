#title boost asio http server 4 with coroutines 
ln -s /Archive2/d5/a5651acef25db6/main.cpp server.hpp
ln -s /Archive2/c6/6d5ff21c4ac2a5/main.cpp server.cpp
ln -s /Archive2/43/319605fd30f5f6/main.cpp request_parser.hpp
ln -s /Archive2/c5/599b923f29c39a/main.cpp request_parser.cpp
ln -s /Archive2/f0/919f140030a58b/main.cpp request.hpp
ln -s /Archive2/1e/97d56cff292392/main.cpp header.hpp
ln -s /Archive2/27/afa3682141a9b3/main.cpp file_handler.hpp
ln -s /Archive2/93/58f7f1591165cc/main.cpp file_handler.cpp
ln -s /Archive2/4a/b74bffffb97200/main.cpp mime_types.hpp
ln -s /Archive2/22/c48c37c1bbe2f0/main.cpp mime_types.cpp
ln -s /Archive2/05/69c25f5c3c3486/main.cpp reply.hpp
ln -s /Archive2/b6/44523f321fe29f/main.cpp reply.cpp
g++ *.cpp -O2 -lboost_system && ./a.out 0.0.0 80 .