#include <iostream>
#define my auto
#define sub int
#define print std::cout <<

sub main() {
    my $x = 0;
    for (my $i = 0; $i < 10; ++$i) {
        print $i;
    }
    return 0;
}

#pragma /*
main;
#pragma */
