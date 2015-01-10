#title Quiz: rock, paper and scissors
g++ -std=c++11 -O2 -pthread main.cpp && ./a.out && echo $? | sed -e s',.,\*,'