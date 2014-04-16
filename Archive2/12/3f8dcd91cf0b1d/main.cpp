#include <iostream>
#include <atomic>
#include <memory>
#include <iostream>

#include <memory>
#include <utility>
#include <type_traits>

using namespace std;


// make unique: https://bitbucket.org/KjellKod/g3log/src/22ad66dcac2c3f691e9b6599e82a239417caf6f5/g2log/src/std2_make_unique.hpp?at=default
namespace std2 {
  namespace impl_fut_stl {

    template<typename T, typename ... Args>
    std::unique_ptr<T> make_unique_helper(std::false_type, Args&&... args) {
      return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
    }

    template<typename T, typename ... Args>
    std::unique_ptr<T> make_unique_helper(std::true_type, Args&&... args) {
      static_assert(std::extent<T>::value == 0, "make_unique<T[N]>() is forbidden, please use make_unique<T[]>(),");
      typedef typename std::remove_extent<T>::type U;
      return std::unique_ptr<T>(new U[sizeof...(Args)] {std::forward<Args>(args)...});
    }
  }

  template<typename T, typename ... Args>
  std::unique_ptr<T> make_unique(Args&&... args) {
    return impl_fut_stl::make_unique_helper<T>(
            std::is_array<T>(), std::forward<Args>(args)...);
  }
}




struct PseudoType {
    // usingn operator()() for sadistic purposes
	void operator()(const std::string& arg) { cout << "Hello " << arg << std::endl; }
	void call(const std::string& arg) { cout << "Hello " << arg << std::endl; }
};

int main() {
	PseudoType h; 
	h("normal object");
	h.call("test from normal object");
	
	
	std::unique_ptr<PseudoType> p {new PseudoType};
	p->operator()("Unique_ptr");
	
	// try 1:
	// this wont compile. copy is deleted.
	//std::atomic<std::unique_ptr<PseudoType>> a(std2::make_unique<std::unique_ptr<PseudoType>>());
	
	// try 2: will also not compile
	std::atomic<std::unique_ptr<PseudoType>> a;
	a.store(std2::make_unique<PseudoType>());
	for (size_t index = 0; index < 100; ++index){
	   a.load()->call("UNSAFE test"); // this WILL crash eventually
	}
	
	// try 3: what can we also tell regarding this construct copyability
	// Unfortunately gcc does not yet support std::is_trivially_copyable
	typedef std::unique_ptr<PseudoType>  UniquePtrType;
	//std::cout << "Is copyable: " << std::is_trivially_copyable<UniquePtrType>::value

    // try 4: using gcc's internal 'has_trivial_copy'
	std::cout << "Is copyable " << __has_trivial_copy(UniquePtrType);
	
	return 0;
}