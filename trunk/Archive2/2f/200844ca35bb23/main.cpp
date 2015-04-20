#include <memory>
#include <iostream>
#include <cassert>
#include <future>
#include <atomic>
#include <mutex>
#include <condition_variable>

#include <utility>
namespace channel_private {

template <typename T>
struct shared_data
{
    shared_data() : has_data{false} {}
	T data;
	bool has_data;
	std::mutex mutex;
	std::condition_variable cv;
};

}

template <typename T>
class input_channel;

template <typename T>
class output_channel
{
	template <typename T2>
	friend class input_channel;
	template<typename T2>
	friend std::pair<output_channel<T2>, input_channel<T2> > make_channels();
public:
	output_channel() = default;
	~output_channel() = default;
	output_channel(const output_channel<T> &o) = default;
	output_channel(output_channel<T> &&o) = default;

	output_channel &operator=(const output_channel<T> &o) = default;

	void create() {
		data = std::make_shared<channel_private::shared_data<T>>();
	}

	void send(T &&v) {
		std::unique_lock<std::mutex> lk(data->mutex);
		if (data->has_data) {
			data->cv.wait(lk, [this]() {
				return !data->has_data;
			});
		}
		data->has_data = true;
		data->data = std::move(v);
		lk.unlock();
		data->cv.notify_all();
	}

private:
	output_channel(const std::shared_ptr<channel_private::shared_data<T>> &d) : data(d) {}
	std::shared_ptr<channel_private::shared_data<T>> data;
};

template <typename T>
class input_channel
{
	template<typename T2>
	friend std::pair<output_channel<T2>, input_channel<T2> > make_channels();
public:
	input_channel() = default;
	~input_channel() = default;
	input_channel(const input_channel<T> &o) = default;
	input_channel(input_channel<T> &&o) = default;

	input_channel &operator=(const input_channel<T> &o) = default;

	void create(const output_channel<T> &ochannel) {
		data = ochannel.data;
	}

	T get() {
		std::unique_lock<std::mutex> lk(data->mutex);
		if (!data->has_data) {
			data->cv.wait(lk, [this]() {
				return data->has_data;
			});
		}
		data->has_data = false;

		T v = std::move(data->data);
		lk.unlock();
		data->cv.notify_all();
		return v;
	}

private:
	input_channel(const std::shared_ptr<channel_private::shared_data<T>> &d) : data(d) {}

	std::shared_ptr<channel_private::shared_data<T>> data;
};



template<typename T>
std::pair<output_channel<T>, input_channel<T> > make_channels()
{
	using namespace channel_private;
	auto data = std::make_shared<shared_data<T>>();

	return std::make_pair(output_channel<T>(data), input_channel<T>(data));
}




struct TestData {
	int num;
	bool stop;
};

input_channel<TestData> ichannel;
output_channel<TestData> ochannel;

void consumer() {
	while(true) {

		TestData data = ichannel.get();
		if (data.stop) {
			std::cout << "Stop\n";
			return;
		}
		std::cout << "Num: " << data.num << std::endl;
	}

}

void worker() {
	TestData data;
	for (int i = 0; i < 10; i++) {
		data.num = i;
		data.stop = false;
		ochannel.send(std::move(data));
	}
	data.num = 0;
	data.stop = true;
	ochannel.send(std::move(data));
}


int main()
{
	auto channels = make_channels<TestData>();
	ochannel = channels.first;
	ichannel = channels.second;
	std::cout << "Starting worker" << std::endl;
	std::thread thread(worker);
	std::cout << "Staring consumer" << std::endl;
	consumer();
	thread.join();
	std::cout << "Finished" << std::endl;
}

