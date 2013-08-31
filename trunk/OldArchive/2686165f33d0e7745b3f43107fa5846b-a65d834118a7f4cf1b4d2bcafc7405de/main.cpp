#include <cstdlib>
#include <iostream>
#include <vector>
#include <array>

int main()
{
    std::array<std::vector<bool>, 2> lamps;
    auto row_iter = lamps.begin();
    char c;
    while (std::cin.get(c) && row_iter != lamps.end()){
        switch (c){
        case '0':
            row_iter->push_back(false);
            break;
        case '1':
            row_iter->push_back(true);
            break;
        case '\n':
            ++row_iter;
            break;
        default:
            std::cerr << "Unexpected input char "
                      << static_cast<int>(c) << std::endl;
            return EXIT_FAILURE;
        }
    }
    
    std::vector<bool>& row1 = lamps[0];
    std::vector<bool>& row2 = lamps[1];
    if (row1.size() != row2.size()) {
        std::cerr << "Rows must be the same length" << std::endl;
        return EXIT_FAILURE;
    }
    
    row1.push_back(false);
    row2.push_back(false);
    unsigned int col_flips = 0;
    unsigned int changes = 0;
    bool prev1 = false, prev2 = false, both_changed = false;
    for (auto iter1=row1.cbegin(), iter2=row2.cbegin();
         iter1 != row1.cend() && iter2 != row2.cend();
         ++iter1, ++iter2) {
        unsigned int col_changes = (*iter1 != prev1);
        col_changes += (*iter2 != prev2);
        if (col_changes == 2) {
            if (both_changed) {
                changes -= 2;
                ++col_flips;
                both_changed = false;
            } else {
                changes += col_changes;
                both_changed = true;
            }
        } else {
            changes += col_changes;
            both_changed = false;
        }
        prev1 = *iter1;
        prev2 = *iter2;
    }
    
    std::cout << col_flips + changes/2 << std::endl;
    return EXIT_SUCCESS;
}