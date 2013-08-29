set +x
cat cmd.sh | tail -n2 | xargs -I {} echo "+ {}"
g++ -std=c++11 -O2 -Wall -pedantic -pthread main.cpp
echo "one two three" | ./a.out