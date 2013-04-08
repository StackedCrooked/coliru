ln -s /Archive/f838230fedff8849bedac6ec0f61472b-50d9cfc8a1d350e7409e81e87c2653ba/main.cpp Message.h
ln -s /Archive/298c5c1c1083e1da89fdcbbcdd9be51e-e17314ffe197211f76da96dbcc1b254c/main.cpp MessageServer.h
g++ -std=gnu++0x -pthread main.cpp -lboost_system -lboost_thread && ./a.out