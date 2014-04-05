#include <queue>
#include <iostream>
#include <cassert>

using std::queue;

void inputError()
{
    if(std::cin.eof()) {
        std::cerr << "Goodbye\n";
        exit(255);
    }
    std::cout << "Invalid input, retry...\n";
    std::cin.clear();
    std::cin.ignore(1024, '\n');
}

template <class T> void moveNthFront(queue<T> q) {
    // A temporary queue is held here to change data
    std::queue<T> tempQ;

    std::cout << "Enter position of the element you want to move to the front..." << std::endl;
    int pos;
    do {
        std::cout << "Ranges from 0 to " << q.size() << ": ";

        if (std::cin >> pos
                && pos > 0 
                && size_t(pos) <= q.size()) 
        { 
            break; // valid input
        }
        inputError();
    } while(true);

    while(--pos) {
        tempQ.push(q.front());
        q.pop();
    }

    if(!tempQ.empty()) {
        T chosenElement = tempQ.front();
        tempQ.pop();

        while(!tempQ.empty()) {
            q.push(tempQ.front());
            tempQ.pop();
        }

        q.push(chosenElement);
    }

    std::cout << q << std::endl;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, queue<T> queueCopy) {
    os << "{ ";
    while(!queueCopy.empty()) {
        os << queueCopy.front() << " ";
        queueCopy.pop();
    }
    return os << "}";
}

template <class T>
queue<T> fillQueue(size_t qSize) {
    queue<T> data;

    // loop for the user to enter qSize values
    T v;
    while(data.size() < qSize) {
        std::cout << "Current data: " << data << "\n";
        std::cout << "Enter data here for the queue: ";
        if(std::cin >> v) {
            data.push(v);
        } else {
            inputError();
        }
    }
    return data;
}

int main() {
    auto data = fillQueue<int>(5);
    std::cout << "Final data: " << data << "\n";
    moveNthFront(data);
}
