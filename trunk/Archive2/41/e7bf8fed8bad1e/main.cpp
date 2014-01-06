#include <iostream>

enum class ECHO { OFF, ON };

void echo( ECHO status )
{
    std::cout << status == ECHO::OFF ? "off" : "on";
}

int main() { echo( ECHO::OFF ); }