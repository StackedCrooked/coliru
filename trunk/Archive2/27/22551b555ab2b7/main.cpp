#include <iostream>
#include <fstream>
using namespace std;

int chooseKey() {
    cout << "Give a number from 1-26: ";
    int key_number;
    while((!(cin >> key_number)) || (key_number < 1 || key_number > 26)) {
        cout << "Your number have to be from 1-26 (" << key_number << "). Retry: ";
        cin.clear();
    }
    return key_number;
}

template <typename InIt, typename OutIt>
void encryption(InIt f, InIt l, OutIt out, int key) {
    for (InIt ptemp = f; ptemp != l; ++ptemp)
    {
        if(isalpha(*ptemp))
        {
            char base = islower(*ptemp)? 'a' : 'A';
            *out++ = base + (*ptemp - base + key) % 26;
        } else
            *out++ = *ptemp;
    }
}

void Caesar(const char *inputFile, const char *outputFile, int key, int mode) {
    ifstream input(inputFile);
    ofstream output(outputFile);

    istreambuf_iterator<char> init(input), end;
    ostreambuf_iterator<char> outit(output);

    encryption(init, end, outit, mode? key : -key);
}

int main() {
    int key, mode;
    key = chooseKey();
    cout << "1 or 0: ";
    cin >> mode;
    Caesar("main.cpp", "-", key, mode);
}

