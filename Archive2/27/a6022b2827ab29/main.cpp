#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <boost/make_shared.hpp>
#include <boost/thread/future.hpp>
#include <iostream>
#include <string>
#include <set>

struct Task
{
    virtual ~Task() = default;
	virtual void execute() {}
	virtual void display_debug() { std::cout << __FUNCTION__ << static_cast<void*>(this) << "\n"; }
};

std::set<Task*> get_tasks()
{
	static std::set<Task*> data{ new Task, new Task };

	return data;
}

int main() {
	struct { boost::asio::io_service io_service; } impl_instance;
	auto impl = &impl_instance;

	std::vector<boost::shared_future<Task*>> futures;
	std::set<Task*> tasks = get_tasks();

	for (Task* t : tasks) {
		typedef boost::packaged_task<Task*> task_t;
		task_t wrap([t]() -> Task* {
			t->execute();
			return t;
		});

		auto fut = wrap.get_future();
		futures.push_back(std::move(fut));

		impl->io_service.post(boost::bind(&task_t::operator(), boost::make_shared<task_t>(std::move(wrap))));
	}

	boost::thread th([&]{ impl->io_service.run(); });

	while (!futures.empty()) {
		auto j = boost::wait_for_any(futures.begin(), futures.end());
		auto fut = *j;
		futures.erase(j);

		Task* task = fut.get();
		task->display_debug();

		// optionally:
		// tasks.erase(task);
	}

	th.join();
}