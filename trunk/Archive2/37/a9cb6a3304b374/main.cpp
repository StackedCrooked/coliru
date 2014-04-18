#include <vector>
#include <iostream>
#include <fstream>

struct row {
    int a;
    int b;
};

std::istream& operator>>(std::istream& in, row& data) 
{
    return in >> data.a >> data.b;
}

std::vector<row> get_data(const char* filename) {
    std::ifstream file(filename);
    if (!file)
        throw std::std::ios_base::failure(filename + std::string(" not found"));
    std::vector<row> data(std::istream_iterator<row>(file), std::istream_iterator<row>());
    if (file.eof()==false)
        throw std::std::ios_base::failure(std::string("invalid data in ") + filename);
    return data;
}

int main() {
    std::vector<row> data = get_data("myfile.txt");
}
