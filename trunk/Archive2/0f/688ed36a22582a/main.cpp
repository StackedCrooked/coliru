#include <iostream>
#include <memory>
#include <string>
#include <vector>

int globalCount = 0;

void printCount(const int * const count) {
    globalCount += *count;
    std::cout << "count: " << *count << std::endl;
}

bool equiv_cyc(const std::string & s1, const std::string & s2) {
    int counter = 0;
    std::unique_ptr<int, decltype(&printCount)> counerScope(&counter, &printCount);
    
    const std::size_t size = s1.length();
    if (size != s2.length()) {
        return false;
    }

    std::size_t s1offset = 0;
    std::size_t s2offset = 0;
    //it is not of importance where in the string we start the comparison
    while (s1offset < size && s2offset < size) {
        for (std::size_t i = 0; i < size; ++i) {
            ++counter;
            const bool equal = s1[(s1offset + i) % size] == s2[(s2offset + i) % size];
            const bool end = i == size-1;
            //std::cout << '(' << s1offset << '|' << s2offset << " + " << i << ") % " << size << " = " << ((s1offset + i) % size) << '|' << ((s2offset + i) % size) << ' ' << equal << std::endl;
            if (!equal) {
                //i is the number of chars we checked already
                //if (s1[(s1offset + i) % size] < s2[(s2offset + i) % size]) {//no clue
                    i = i == 0 ? 1 : i;//move at least one char
                    s1offset += 1;
                //} else {
                    //i = i == 0 ? 1 : i;
                  //  s2offset += i;
                //}
                break;
            } else if (end) {//we checked size consecutive chars
                return true;
            }
        }
    }
    return false;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (auto& el : vec)
    {
        os << el << ' ';
    }
    return os;
}

int main()
{
    std::vector<std::string> words = {
        "Hello", "from", "GCC", __VERSION__, "!"
    };
    std::cout << words << std::endl;
    std::cout << std::boolalpha;
    //std::cout << equiv_cyc("zyxwvut", "yxwvutz") << std::endl;
    //std::cout << equiv_cyc("abcdefg", "bcdefga") << std::endl;
    std::cout << equiv_cyc("stackstacks", "stacksstack") << std::endl;
    std::cout << equiv_cyc("stackstacksstackstacked", "edstackstacksstackstack") << std::endl;
    std::cout << equiv_cyc("stackstacksstackstacked", "stackstackedstackstacks") << std::endl;
    std::cout << equiv_cyc("stackoverflow", "ztackoverflow") << std::endl;
    std::cout << equiv_cyc("stackoverflow", "ackoverflowst") << std::endl;
    std::cout << equiv_cyc("stackoverflow", "overflowstack") << std::endl;
    std::cout << equiv_cyc("stackoverflow", "stackoverflwo") << std::endl;
    std::cout << equiv_cyc("stackoverflow", "tackoverflwos") << std::endl;
    std::cout << globalCount << std::endl;
}
