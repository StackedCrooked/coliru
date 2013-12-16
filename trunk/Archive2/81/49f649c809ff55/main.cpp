#include <iostream>
#include <sstream>
#include <thread>
#include <mutex>
#include <functional>
#include <condition_variable>
#include <cstdlib>

std::mutex mtx;
std::condition_variable cv;

int turn = 1;

void print_line(std::istream& in_stream, std::ostream& out_stream, int t);

int main(int argc, const char * argv[]){
    std::istringstream input_file_1("ace");
    std::istringstream input_file_2("bdf");
    std::ostream& output_file = std::cout;

    if (!input_file_1 || !input_file_2 || !output_file) {
        std::cout << "Error while opening the input files\n";
        std::exit(EXIT_FAILURE);
    } else {
        std::thread input1(print_line, ref(input_file_1), ref(output_file), 1);
        std::thread input2(print_line, ref(input_file_2), ref(output_file), 2);
        input1.join();
        input2.join();
    }
}

void print_line(std::istream& in_stream, std::ostream& out_stream, int t){
    char temp;
    while (in_stream >> temp) {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [&t] { return turn == t; });
        out_stream << temp;
        turn = (turn == 1) ? 2 : 1;
        cv.notify_all();
    }
}