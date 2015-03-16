#include <iostream>

struct Container {
    Container(int i) { data = i; }

    friend std::ostream& operator<<(std::ostream& os, Container const& c) {
        return os << c.data;
    }
  private:
    int data;
};

void print(Container const& blue, Container const& red) {
    std::cout << "Blue oni is: " << blue << " | Red oni is: " << red << "\n";
}

int main() {
    Container blue_oni(1);
    Container red_oni(0);

    std::cout << "Pre-ASSIGN\n";
    print(blue_oni, red_oni);

    blue_oni = red_oni;

    std::cout << "Post-ASSIGN red to blue\n";
    print(blue_oni, red_oni);
}
