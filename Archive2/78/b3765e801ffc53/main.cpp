#include <functional>
#include <future>
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
	auto future_result_bar = std::async(std::launch::async, thread_function_bar, std::ref(m));
	auto future_result_qux = std::async(std::launch::async, thread_function_qux, std::ref(m));
	std::cout << "foo = " << m["foo"] << '\n';
	std::cout << "foo = " << m["foo"] << '\n';
	std::cout << "foo = " << m["foo"] << '\n';
	future_result_bar.get();
	future_result_qux.get();
	std::cout << "foo = " << m["foo"] << '\n';
	std::cout << "foo = " << m["foo"] << '\n';
	std::cout << "foo = " << m["foo"] << '\n';
}
