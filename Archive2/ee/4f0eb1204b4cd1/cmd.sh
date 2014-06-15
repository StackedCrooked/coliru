g++-4.8 -std=c++11 -Os -Wall -pedantic -pthread main.cpp && ./a.out <<INPUT
name "xy"
entries
{
    entry {
        name "n1"
        val1 "asdf"
        val2 3.5
    }
    entry {
        name "n2"
        val1 "hjkl"
        val2 7.5
    }
}
INPUT