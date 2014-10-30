#define _SCL_SECURE_NO_WARNINGS
#include <boost/asio.hpp>
#include <boost/signals2.hpp>
#include <boost/thread.hpp>
#include <boost/function.hpp>
#include <boost/thread/future.hpp>
#include <iostream>
#include <string>

int main() {
    boost::asio::io_service io_service;

	using Task = boost::function<void()>;
	using TaskId = int;

	boost::signals2::signal<bool(TaskId, int step, int total)> task_progress;
	boost::signals2::signal<void(TaskId)> task_finished;

	/////// POST WORK
	io_service.post([&]() {
		for (int step = 0; step <= 10; ++step) {
			boost::this_thread::sleep_for(boost::chrono::milliseconds(200));
			if (!task_progress(1, step, 10))
				break; // operation canceled
		}
		task_finished(1);
	});

	io_service.post([&]() {
		boost::this_thread::sleep_for(boost::chrono::seconds(1));
		task_finished(2);
	});

	/////// UI REGISTERS CALLBACKS
	task_progress.connect([&](TaskId task, int step, int total)
	{
		io_service.post([=]{ std::cout << "Task " << task << " is " << (100 * step / total) << "% complete\n"; });
		return true; // continue the task
	});

	task_finished.connect([&](TaskId task)
	{
		io_service.post([=]{ std::cout << "Task " << task << " has completed\n"; });
	});

	//////  RUN DEMO
	boost::thread_group tg;
	tg.create_thread([&]{ io_service.run(); });
	tg.create_thread([&]{ io_service.run(); });

	tg.join_all();
}