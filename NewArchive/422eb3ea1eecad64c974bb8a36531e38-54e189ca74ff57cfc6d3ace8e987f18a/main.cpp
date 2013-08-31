#include <algorithm>
//#include <future>
#include <chrono>
#include <iostream>
#include <thread>
#include <vector>

int main(int, char**) {
    std::cout << "Generating data..." << std::endl;
	auto start = std::chrono::high_resolution_clock::now();
	std::vector<double> data(1024 * 1024 * 48);
	auto end = std::chrono::high_resolution_clock::now();
	std::cout << "  allocated in " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << std::endl;

	start = std::chrono::high_resolution_clock::now();
	{
		int i = 0;
		for(auto& elem : data) elem = ++i;
	}
	std::cout << data[0] << " " << data[1] << " " << data[2] << std::endl;
	end = std::chrono::high_resolution_clock::now();
	std::cout << "  generated in " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << std::endl;

	for(float threadCount = 1; threadCount <= 10; ++threadCount) {
		double mean = 0;
		std::vector<std::thread> threads(threadCount);
		std::vector<double> result(threadCount);

		std::cout << "Calculating mean, " << threadCount << " Threads..." << std::endl;
		start = std::chrono::high_resolution_clock::now();
		for(float i = 0; i < threadCount-1; ++i) {
			int offsetStart = i * data.size() / threadCount;
			int offsetEnd = (i+1) * data.size() / threadCount;
			threads[i] = std::thread([&data, &result, i, offsetStart, offsetEnd](){result[i] = std::accumulate(
							std::begin(data) + offsetStart
							, std::begin(data)  + offsetEnd, 0.0);});
		}
		int offset = (threadCount-1) * data.size() / threadCount;
		threads[threadCount-1] = std::thread([&data, &result, threadCount, offset](){result[threadCount-1] = std::accumulate(
						std::begin(data) + offset
						, std::end(data), 0.0);});

		for(auto& t : threads)
			if(t.joinable()) t.join();
		end = std::chrono::high_resolution_clock::now();

		for(auto& r : result)
			mean += r;
		mean /= data.size();

		std::cout << "  Mean=" << mean << " time=" << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << std::endl;
	}
}
