#include <iostream>
#include <type_traits>
#include <set>
#include <memory>
 
class Secret {
 public:
  int get() const {
    return value;
  }
  bool operator<(const Secret& a) const {
    return value < a.value;
  }
  static Secret create(int v) {
    return Secret(v);
  }
 private:
  Secret(int v) : value(v) {}
  int value;
};

template<typename A, typename V>
class point_type
    {
	public:
		point_type(const point_type& other) = default;
		point_type& operator=(const point_type&) = default;
		A const& arg() const {
			return (*a);
		}
		V const& value() const {
			return (*v);
		}
	private:
		std::shared_ptr<A> a;
		std::shared_ptr<V> v;
		point_type(const A& arg) : a(std::make_shared<A>(arg)) {}
		point_type(const std::shared_ptr<A> arg, const V& value) {
			v = std::make_shared<V>(value);
			a = arg;
		}
		point_type(const A& arg, const V& value)  
		{
			try {
				a = std::make_shared<A>(arg);
				v = std::make_shared<V>(value);
			}
			catch (...) {
				a.reset();
				v.reset();
				throw;
			}
		}
	};

typedef point_type<Secret, Secret> typ;
 
int main() {
    std::cout << std::boolalpha
    
            << "move-constructible? "
              << std::is_move_constructible<std::multiset<typ>>::value << '\n'
              
              << "nothrow move-constructible? "
              << std::is_nothrow_move_constructible<std::multiset<typ>>::value << '\n'
                            
              << "nothrow move-assignable? "
              << std::is_nothrow_move_assignable<std::multiset<typ>>::value << '\n'
              
              << "move-assignable? "
              << std::is_move_assignable<std::multiset<typ>>::value << '\n';
              
}