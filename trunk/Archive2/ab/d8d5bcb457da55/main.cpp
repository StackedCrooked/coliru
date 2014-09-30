#include <iostream>
#include <string>

class Singer {
    friend std::ostream& Christmas(std::ostream& out);
    Singer(std::ostream& out) : out(out) {}
    std::ostream& sing(int day, int count) {
      return day ? count <= day ? sing(day, count + 1) << (count == 1 && day > 1 ? "and " : "")
                                                       << gift[count - 1] << '\n'
                                : sing(day - 1, 1) << "\nOn the "
                                                   << day
                                                   << " day of Christmas, "
                                                      "my true love gave to me:\n"
                 : out;
    }
  private:
    std::ostream& out;
    static const char *gift[12];
};
const char *Singer::gift[] = {
        "a Partridge in a Pear Tree,",
        "2 Turtle Doves,",
        "3 French Hens,",
        "4 Calling Birds,",
        "5 Gold Rings,",
        "6 Geese-a-Laying,",
        "7 Swans-a-Swimming,",
        "8 Maids-a-Milking,",
        "9 Ladies Dancing,",
        "10 Lords-a-Leaping,",
        "11 Pipers Piping,",
        "12 Drummers Drumming."
};

std::ostream& Christmas(std::ostream& out) { return Singer(out).sing(12,1); }

int main() {
    std::cout << Christmas;
    return 0;
}
