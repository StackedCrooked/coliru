#include <iostream>
#include <random>

int main(int argc, char *argv[])
{
    // generate random integers from 1 to 3
    std::uniform_int_distribution<int> dist(1, 3);
    std::random_device rnd;

    int iterations = 100000;
    int switchWins = 0;
    int stickWins = 0;

    for (int i = 0; i < iterations; ++i) {
        int answer = dist(rnd); // random number 1-3

        int choice = dist(rnd); // make a random choice 1-3

        // "reveal" a door that is incorrect and not the already chosen door
        int reveal;
        do { reveal = dist(rnd); }
        while (reveal == answer || reveal == choice);

        // get the remaining door
        int remaining = 1;
        while (remaining == reveal || remaining == choice) remaining++;

        // the outcome if we "stick"
        if (answer == choice) stickWins++;

        // the outcome if we "switch"
        else if (answer == remaining) switchWins++;
    }

    float switchWinPct = (float)switchWins/iterations * 100;
    float stickWinPct = (float)stickWins/iterations * 100;

    std::cout << R"("Switch" wins:)" << switchWins << " (" << switchWinPct << "%)" << std::endl;
    std::cout << R"("Stick" wins:)" << stickWins << " (" << stickWinPct << "%)" << std::endl;

    return 0;
}

