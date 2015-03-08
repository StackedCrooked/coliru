# include <chrono>
# include <iostream>
# include <thread>
# include <mutex>

void displayDataFromFile() { std::cout << "FROM file!" << std::endl; }
bool askContinueWaiting(const char * message) {
    std::cout << message << std::endl;
    return true;    
}

void f()
{
    std::timed_mutex fileMutex;
    // …
    while (true) {
        using namespace std::literals::chrono_literals;
        if (fileMutex.try_lock_for(5s)) {
            std::lock_guard<std::timed_mutex> lock(fileMutex, std::adopt_lock);
            displayDataFromFile();
            break;
        }
        else if (! askContinueWaiting("The file is not available yet."))
            break;
    }
}

int main()
{
    f();
}
