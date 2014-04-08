#include <functional>
#include <iostream>
#include <map>
#include <string>
#include <thread>

using Map = std::map<std::string, std::string>;

void thread_function_bar(Map & map)
{
    map["foo"] = "bar";
	return;
}

void thread_function_qux(Map & map)
{
	map["foo"] = "qux";
	return;
}

int main()
{
	Map m;
	std::thread worker_thread_bar(thread_function_bar, std::ref(m));
	std::thread worker_thread_qux(thread_function_qux, std::ref(m));
	std::cout << "foo = " << m["foo"] << '\n';
    std::cout << "foo = " << m["foo"] << '\n';
    std::cout << "foo = " << m["foo"] << '\n';
	worker_thread_bar.join();
	worker_thread_qux.join();
    std::cout << "foo = " << m["foo"] << '\n';
    std::cout << "foo = " << m["foo"] << '\n';
    std::cout << "foo = " << m["foo"] << '\n';
}
