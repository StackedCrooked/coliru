#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

class Tabular {
private:
    std::ifstream in;
    std::stringstream ss;
    std::string temp;
    size_t count;
    size_t col_size;
public:
    Tabular(): count(0), col_size(0) {}
    void open(const std::string& str) {
        in.open(str);
        std::getline(in,temp);
        ss << "<table border=\"1\">\n<tr>";
        // Parse the header
        for(auto&& i : temp) {
            if(count == 0) {
                ss << "<th>";
                count = 1;
            }
            if(i == '|') {
                ++col_size;
                count = 0;
                ss << "</th>";
                continue;
            }
            ss << i;
        }
        ss << "</tr>\n";
        count = 0;
        // Parse the data
        while(std::getline(in,temp,'|')) {
            if(count == 0) {
                ss << "<tr>";
            }
            ss << "<td>" << temp << "</td>";
            ++count;
            if(count == col_size) {
                std::getline(in,temp);
                ss << "<td>" << temp << "</td></tr>\n";
                count = 0;
            }
        }
    }
    std::string getTable() {
        ss << "</table>\n";
        return ss.str();
    }
};

int main() {
    Tabular table;
    table.open("example.txt");
    std::cout << table.getTable();
}