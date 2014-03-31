#include <boost/multi_array.hpp>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <vector>

template<typename FIter>
FIter longest_elem(FIter b, FIter e) {
    return std::max_element(b, e, [](auto lhs, auto rhs) { return lhs.size() < rhs.size(); });
}

struct table {
    using array_type = boost::multi_array<std::string, 2>;
    array_type data;
    std::size_t gap;
    
    table(std::size_t width, std::size_t height) : data(boost::extents[width][height]) {}
    
    void print(std::ostream& os) const {
        using range = boost::multi_array_types::index_range;
        std::vector<int> column_sizes;
        
        for (auto const& column : data)
            column_sizes.push_back((*longest_elem(column.begin(), column.end())).size());
            
        std::string gap_s(' ', gap);
        auto print_row = [&](auto row) {
            os << std::setw(column_sizes[0]) << row[0];
            for (std::size_t i = 1; i < row.size(); ++i)
                os << gap_s << std::setw(column_sizes[i]) << row[i];
            std::cout << '\n';
        };
        
        auto header = data[boost::indices[0][range(0,column_sizes.size())]];
        print_row(header);
        std::cout << std::setw(std::accumulate(column_sizes.begin(), column_sizes.end(), 0) + column_sizes.size()*gap - gap) << std::setfill('=') << "" << "\n";
        std::cout << std::setfill(' ');
        for (std::size_t i = 1; i < data.size(); ++i)
            print_row(data[boost::indices[i][range(0,column_sizes.size())]]);
    }
};

int main() {
    table example(2, 2);
    example.data[0][0] = "Left header";
    example.data[0][1] = "Right header";
    example.data[1][0] = "Data";
    example.data[1][1] = "More very long data";
    example.print(std::cout);
}