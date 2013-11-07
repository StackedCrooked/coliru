#include <iostream>
#include <thread>
#include <future>
#include <mutex>
#include <queue>
#include <string>

struct request { std::string req; };

std::queue<request> q;
std::mutex queue_mutex;

void execQueue(request r) {
    std::cout << "req is: " << r.req << std::endl; // req is a string field
}

bool sched(std::queue<request>& qr) {
    std::thread pt1, pt2;

	{
		std::lock_guard<std::mutex> lk(queue_mutex);
		if (!qr.empty()) {
			auto t1 = std::move(qr.front());
			qr.pop();
			pt1 = std::thread(&execQueue, std::move(t1));
		}
		if (!qr.empty()) {
			auto t2 = std::move(qr.front());
			qr.pop();
			pt2 = std::thread(&execQueue, std::move(t2));
		}
	}

	if (pt1.joinable()) pt1.join();
	if (pt2.joinable()) pt2.join();

    return true;
}

int main()
{
	auto fut = std::async(sched, std::ref(q));
	if (!fut.get()) 
		std::cout << "error" << std::endl;
}

