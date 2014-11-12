#include <cstdio>
#include <string>

void seven_segment_display(std::string number)
{
    auto row = [&](auto r)
    {
        for (char ch : number) std::printf("%.3s ", r + (ch - '0') * 3);
        std::putchar('\n');
    };
    row(" _     _  _     _  _  _  _  _ ");
    row("| |  | _| _||_||_ |_   ||_||_|");
    row("|_|  ||_  _|  | _||_|  ||_| _|");
}

int main()
{
    seven_segment_display("1920385764");
}
