#include <iterator>
#include <fstream>
#include <algorithm>
#include <iostream>

struct Record { 
    std::string name; int score; 
    friend std::istream& operator>>(std::istream& is, Record& r)       { return is >> r.name         >> r.score; }
    friend std::ostream& operator<<(std::ostream& os, Record const& r) { return os << r.name << "\t" << r.score; }

    bool operator<(Record const& other) const {
        return other.score < score;
    }
};

int main()
{
    std::ifstream ifs("input.txt");
    std::vector<Record> const insert { Record { "Jodi", 70 } };
    
    std::merge(
            std::istream_iterator<Record>(ifs), {}, 
            insert.begin(), insert.end(),
            std::ostream_iterator<Record>(std::cout, "\n"));
}
