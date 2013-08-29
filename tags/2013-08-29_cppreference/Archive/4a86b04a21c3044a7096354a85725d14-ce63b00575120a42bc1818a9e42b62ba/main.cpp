#include <vector>
#include <iostream>

struct big_data_type {
    double state;
	big_data_type( double d ):state(d) { ++counter; ++create_counter; }
	big_data_type():state(0.) { ++counter; }
	big_data_type( big_data_type const& o ): state(o.state) { ++counter; }
    big_data_type( big_data_type && o ): state(o.state) { ++move_counter; }
	big_data_type& operator=( big_data_type const& o ) {
		state = o.state;
		++counter;
		return *this;
	}
    big_data_type& operator=( big_data_type && o ) {
		state = o.state;
		++move_counter;
		return *this;
	}
	static int counter;
    static int create_counter;
    static int move_counter;
};
int big_data_type::move_counter = 0;
int big_data_type::create_counter = 0;
int big_data_type::counter = 0;

std::vector<big_data_type>& make_vector( int i, std::vector<big_data_type>& tmp ) {
	tmp.resize(0);
	tmp.reserve(1000);
	for( int j = 0; j < 10+i/100; ++j ) {
		tmp.emplace_back( 100. - j/10. );
	}
	return tmp;
}
std::vector<big_data_type> make_vector2( int i ) {
    std::vector<big_data_type> tmp;
    tmp.resize(0);
	tmp.reserve(1000);
	for( int j = 0; j < 10+i/100; ++j ) {
		tmp.emplace_back( 100. - j/10. );
	}
	return tmp;
}
enum option { a, b, c, d, e };
void test(option op) {
	std::vector<std::vector<big_data_type> > table;
	std::vector<big_data_type> tmp;
	for(int i=0; i!=10; ++i) {
        switch(op) {
            case a:
                table.emplace_back(make_vector(i, tmp));
                break;
            case b:
                tmp = make_vector2(i);
                table.emplace_back(tmp);
                break;
            case c:
                tmp = make_vector2(i);
                table.emplace_back(std::move(tmp));
                break;
            case d:
                table.emplace_back(make_vector2(i));
                break;
            case e:
                std::vector<big_data_type> result;
                make_vector(i, tmp);
                result.reserve( tmp.size() );
                result.insert( result.end(), std::make_move_iterator( tmp.begin() ),std::make_move_iterator( tmp.end() ) );
                table.emplace_back(std::move(result));
                break;
        }
	}
	std::cout << "Big data copied or created:" << big_data_type::counter << "\n";
    big_data_type::counter = 0;
    std::cout << "Big data created:" << big_data_type::create_counter << "\n";
    big_data_type::create_counter = 0;
    std::cout << "Big data moved:" << big_data_type::move_counter << "\n";
    big_data_type::move_counter = 0;
    std::size_t cap = 0;
    for (auto&& v:table)
        cap += v.capacity();
    std::cout << "Total capacity at end:" << cap << "\n";
}

int main() {
    std::cout << "A\n";
    test(a);
    std::cout << "B\n";
    test(b);
    std::cout << "C\n";
    test(c);
    std::cout << "D\n";
    test(d);
    std::cout << "E\n";
    test(e);
}
