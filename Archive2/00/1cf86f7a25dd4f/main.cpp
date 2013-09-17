#include <stdio.h>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <fstream>
#include <time.h>
#include <string>
#include <algorithm>

unsigned count1(FILE *infile, char c) { 
    int ch;
    unsigned count = 0;

    while (EOF != (ch=getc(infile)))
        if (ch == c)
            ++count;
    return count;
}

unsigned int count2(FILE *infile, char c) { 
    static char buffer[8192];
    int size;
    unsigned int count = 0;

    while (0 < (size = fread(buffer, 1, sizeof(buffer), infile)))
        for (int i=0; i<size; i++)
            if (buffer[i] == c)
                ++count;
    return count;
}

unsigned count3(std::istream &infile, char c) {    
    return std::count(std::istreambuf_iterator<char>(infile), 
                    std::istreambuf_iterator<char>(), c);
}

unsigned count4(std::istream &infile, char c) {    
    return std::count(std::istream_iterator<char>(infile), 
                    std::istream_iterator<char>(), c);
}

unsigned int count5(std::istream &infile, char c) {
    static char buffer[8192];
    unsigned int count = 0;

    while (infile.read(buffer, sizeof(buffer)))
        count += std::count(buffer, buffer+infile.gcount(), c);
    return count;
}

unsigned count6(std::istream &infile, char c) {
    unsigned int count = 0;
    char ch;

    while (infile >> ch)
        if (ch == c)
            ++count;
    return count;
}

template <class F, class T>
void timer(F f, T &t, std::string const &title) { 
    unsigned count;
    clock_t start = clock();
    count = f(t, 'N');
    clock_t stop = clock();
    std::cout << std::left << std::setw(30) << title << "\tCount: " << count;
    std::cout << "\tTime: " << double(stop-start)/CLOCKS_PER_SEC << "\n";
}

int main() {
    char const *name = "equivs2.txt";

    FILE *infile=fopen(name, "r");

    timer(count1, infile, "ignore");

    rewind(infile);
    timer(count1, infile, "using getc");

    rewind(infile);
    timer(count2, infile, "using fread");

    fclose(infile);

    std::ifstream in2(name);
    timer(count3, in2, "ignore");

    in2.clear();
    in2.seekg(0);
    timer(count3, in2, "using streambuf iterators");

    in2.clear();
    in2.seekg(0);
    timer(count4, in2, "using stream iterators");

    in2.clear();
    in2.seekg(0);
    timer(count5, in2, "using istream::read");

    in2.clear();
    in2.seekg(0);
    timer(count6, in2, "using operator>>");

    return 0;
}