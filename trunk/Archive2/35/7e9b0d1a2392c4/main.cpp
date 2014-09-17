#include <iostream>
#include <future>
#include <vector>
#include <memory>
#include <functional>

    template<class T>
    using loader = std::function< std::vector<T>(size_t max) >;
    
    template<class T>
    using stream_data = std::shared_ptr< std::vector< std::future<T> > >;
    
    namespace details {
      template<class T>
      T streaming_load_some( loader<T> l, size_t start, stream_data<T> data ) {
        auto loaded = l(data->size()-start);
        // populate the stuff after start first, so they are ready:
        for( size_t i = 1; i < loaded.size(); ++i ) {
          std::promise<T> promise;
          promise.set_value( std::move(loaded[i]) );
          (*data)[start+i] = promise.get_future();
        }
        if (start+loaded.size() < data->size()) {
          // recurse:
          std::size_t new_start = start+loaded.size();
          (*data)[new_start] = std::async(
            std::launch::async,
            [l, new_start, data]{return streaming_load_some<T>( l, new_start, data );}
          );
        }
        // populate the future:
        return std::move(loaded.front());
      }
    }
    template<class T>
    stream_data< T >
    streaming_loader( loader<T> l, size_t n ) {
      auto retval = std::make_shared<std::vector< std::future<T> >>(n);
      if (retval->empty()) return retval;
      retval->front() = std::async(
        std::launch::async,
        [retval, l]()->T{return details::streaming_load_some<T>( l, 0, retval );
      });
      return retval;
    }
struct loader_state {
    int index = 0;
};
struct test_loader {
  std::shared_ptr<loader_state> state; // current loading state stored here
  std::vector<int> operator()( std::size_t max ) const {
  	std::size_t amt = max/2+1; // don't do it all at once -- in real code, make this a reasonable chunk
  	std::vector<int> retval;
  	retval.reserve(amt);
  	for (size_t i = 0; i < amt; ++i) {
  		retval.push_back( -(int)(state->index + i) ); // populate the return value
  	}
    state->index += amt;
  	return retval;
  }
  // in real code, make this constructor do something:
  test_loader():state(std::make_shared<loader_state>()) {}
};
int main() {
	auto data = streaming_loader<int>( test_loader{}, 1024 );
	std::size_t count = 0;
	for( std::future<int>& x : *data ) {
        ++count;
        int value = x.get(); // get data
        
        // process.  In this case, print out 100 in blocks of 10:
        if (count * 100 / data->size() > (count-1) * 100 / data->size())
    		std::cout << value << ", ";
        if (count * 10 / data->size() > (count-1) * 10 / data->size())
        	std::cout << "\n";
	}
	std::cout << std::endl;
	// your code goes here
	return 0;
}