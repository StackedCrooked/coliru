#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>

using namespace std;

string read_file(string filename){
    ifstream f(filename);
    stringstream buffer;
    buffer << f.rdbuf();
    return buffer.str();
}

static vector<double> frequencies = { 8.167, 1.492, 2.782, 4.253, 12.702, 2.228, 2.015, 6.094, 6.966, 0.153, 0.772, 4.025, 2.406, 6.749, 7.507, 1.929, 0.095, 5.987, 6.327, 9.056, 2.758, 0.978, 2.360, 0.150, 1.974, 0.074 };
static string alphabet = "abcdefghijklmnopqrstuvwxyz";
static vector<string> words;

class Generator
{
private:
    unsigned int size;

    Generator* child;

    enum State
    {
        Left,
        Child,
        Right
    } next_state, and_then;
    unsigned int index;

public:

    Generator(unsigned int s) :size(s), next_state(Right), index(0) {

        if (size != 1){
            child = new Generator(size - 1);
        }
        else{
            child = nullptr;
        }
        
    }
    ~Generator(){
        if (child!=nullptr)
            delete child;
    }

    bool next(unsigned int& index1, unsigned int& index2){
        if (size == 1)
            return false;

        if (next_state == Right)
        {
            ++index;
            if (index == size - 1) next_state = Child, and_then = Left;
            index1 = index - 1, index2 = index;
        }
        else if (next_state == Left)
        {
            --index;
            if (index == 0) next_state = Child, and_then = Right;
            index1 = index, index2 = index + 1;
        }else{
            //child

            next_state = and_then;
            if (!child->next(index1, index2)){
                return false;
            }

            if (and_then == Right){
                ++index1;
                ++index2;
            }

        }


        return true;
    }

};



int main(int argc, char* argv[])
{

    Generator gen(12);

    auto start = std::chrono::system_clock::now();

    string permuted_alphabet = alphabet;

    unsigned int index1, index2;
    unsigned int count_swaps = 0;
    while (gen.next(index1, index2)){
        ++count_swaps;
        //printf("swap #%u %u and %u\n", count_swaps, index1, index2);
    }

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::system_clock::now() - start);


    cout << "total swaps: " << count_swaps << "\n";
    cout << "time (ms): " << duration.count() << "\n";

    return 0;
}

