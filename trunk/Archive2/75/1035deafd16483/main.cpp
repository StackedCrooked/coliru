#include <queue>
#include <iostream>
#include <cstdlib>

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

template <class Container> size_t pickIndex(Container const& c)
{
    std::cout << "Enter position of the element you want to move to the front..." << std::endl;
    int n;
    do {
        std::cout << "Ranges from 0 to " << c.size() << ": ";

        if (std::cin >> n
                && n > 0 
                && size_t(n) <= c.size()) 
        { 
            return n;
        }
        inputError();
    } while(true);
}

template <class T> void moveNthFront(queue<T>& q, size_t n) {
    // A temporary queue is held here to change data
    std::queue<T> tempQ;

    while(--n) {
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
    queue<int> data = fillQueue<int>(5);

    std::cout << "Queue filled: " << data << "\n";

    size_t n = pickIndex(data);

    moveNthFront(data, n);

    std::cout << "Queue after moveNthFront: " << data << "\n";
}
