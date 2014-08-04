for a in {1..100}; do echo -e "src:$RANDOM\tdst:$RANDOM"; done | gzip > csv.txt.gz
g++ -std=c++03 -Wall main.cpp -lboost_system -lboost_iostreams -lz && ./a.out