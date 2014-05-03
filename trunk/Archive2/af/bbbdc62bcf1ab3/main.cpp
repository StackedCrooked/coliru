
static const int num_data = 3;
int datum[] = {3, 4};
extern int datum[num_data];

#include <iostream>
int main() {
    std::cout << datum[2];
}