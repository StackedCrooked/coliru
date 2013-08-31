#include <future>
#include <vector>
#include <iostream>

typedef std::vector<double> DataWareHouse;

void run_thread(std::promise<DataWareHouse> data_chunks)
{
    DataWareHouse results;
    results.push_back( 3.14159 );
	data_chunks.set_value(results);
}

std::future<DataWareHouse> do_async_work()
{
    std::promise<DataWareHouse> data_chunks;	
	std::future<DataWareHouse> retval = data_chunks.get_future();
	// DataWareHouse is my customized class
	//data_chunks has a vector<vector<double>> member variable
	std::thread t = std::thread(&run_thread,std::move(data_chunks));
    t.detach(); // do this or seg fault
	return retval;
}

int main() {
	std::future<DataWareHouse> result = do_async_work();
	DataWareHouse vec = result.get(); // block and get the data
	for (double d: vec) {
		std::cout << d << "\n";
	}
}
