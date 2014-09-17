#include <iostream>
#include <future>
#include <functional>
#include <vector>
#include <memory>

// if it returns empty, there is nothing more to load:
template<class T>
using loader = std::function< std::vector<T>() >;

template<class T>
struct next_data;

template<class T>
struct streamer {
  std::vector<T> data;
  std::unique_ptr<next_data<T>> next;
};

template<class T>
struct next_data:std::future<streamer<T>> {
    using parent = std::future<streamer<T>>;
    using parent::parent;
    next_data( parent&& o ):parent(std::move(o)){}
};

template<class T>
streamer<T> stream_step( loader<T> l ) {
    streamer<T> retval;
	retval.data = l();
	if (retval.data.empty())
		return retval;
		
	retval.next.reset( new next_data<T>(std::async( std::launch::async, [l](){ return stream_step(l); })));
	return retval;
}
template<class T>
streamer<T> start_stream( loader<T> l ) {
	streamer<T> retval;
	retval.next.reset( new next_data<T>(std::async( std::launch::async, [l](){ return stream_step(l); })));
	return retval;
}
struct counter {
	std::size_t max;
	std::size_t current = 0;
	counter( std::size_t m ):max(m) {}
	std::vector<int> operator()() {
		std::vector<int> retval;
		std::size_t do_at_most = 100;
		while( current < max && (do_at_most-->0)) {
			retval.push_back( int(current) );
			++current;
		}
		return retval;
	}
};
int main() {
	streamer<int> s = start_stream<int>( counter(1024) );
	
	while(true) {
		for (int x : s.data) {
			std::cout << x << ",";
		}
		std::cout << std::endl;
		if (!s.next)
			break;
		s = std::move(s.next->get());
	}
	// your code goes here
	return 0;
}