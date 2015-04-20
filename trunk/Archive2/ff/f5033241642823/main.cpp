
#include <iostream>
#include <mutex>
#include <condition_variable>
#include <thread>
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
class channel
{
	template<typename T2>
	friend channel<T2> make_channel();
public:
	channel() = default;
	~channel() = default;
	channel(const channel<T> &o) = default;
	channel(channel<T> &&o) = default;

	channel &operator=(const channel<T> &o) = default;

	void create();
	void send(const T &v);
	void send(T &&v);

	T get();

	channel<T> &operator<<(const T &v);
	channel<T> &operator>>(T &v);

private:
	channel(const std::shared_ptr<channel_private::shared_data<T>> &d) : data(d) {}
	std::shared_ptr<channel_private::shared_data<T>> data;
};

template<typename T>
void channel<T>::create() {
	data = std::make_shared<channel_private::shared_data<T>>();
}

template<typename T>
void channel<T>::send(T &&v) {
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

template<typename T>
void channel<T>::send(const T &v) {
	std::unique_lock<std::mutex> lk(data->mutex);
	if (data->has_data) {
		data->cv.wait(lk, [this]() {
			return !data->has_data;
		});
	}
	data->has_data = true;
	data->data = v;
	lk.unlock();
	data->cv.notify_all();
}

template<typename T>
T channel<T>::get() {
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

template<typename T>
channel<T> &channel<T>::operator<<(const T &v) {
	this->send(v);
	return *this;
}

template<typename T>
channel<T> &channel<T>::operator>>(T &v) {
	v = std::move(this->get());
	return *this;
}


template<typename T>
channel<T> make_channel()
{
	auto data = std::make_shared<channel_private::shared_data<T>>();
	return channel<T>(data);
}











//Example
//-----------------------------------------



struct TestData {
	int num;
	bool stop;
};

channel<TestData> c = make_channel<TestData>();

void consumer() {
	while(true) {
		TestData data = c.get();
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
		c << data;
	}
	data.num = 0;
	data.stop = true;
	c << data;
}


int main()
{
	std::cout << "Starting worker" << std::endl;
	std::thread thread(worker);
	std::cout << "Staring consumer" << std::endl;
	consumer();
	thread.join();
	std::cout << "Finished" << std::endl;
}
