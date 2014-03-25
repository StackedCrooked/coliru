for batch_size in 64 512 1024 2048 1; do 
  g++-4.8 -DBATCH_SIZE=${batch_size} -std=c++11 -O2 -Wall -pedantic -pthread main.cpp -ltbb
  printf "batch_size=${batch_size}\twork_counter=$(./a.out)\n"
done | column -t