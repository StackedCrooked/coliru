#include <initializer_list>
#include <array>
#include <iostream>
#include <utility>

struct Special {
private:
    int arf;

public:

	Special (int a) : arf(a) {

	}

	Special (float a) : arf((int)a) {

	}

	Special (double a) : arf((int)a) {

	}

	int Get() {
		return arf;   
	}



	template <typename ... Args>
	static Special Format ( const Special& format, const Args&... args ) {
		Special value = format;
		
		Format<Args...>( value, args... );

		return value;
	}

private:

	template <typename T, typename ... Args>
	static void Format ( Special& value, const T& arg0, const Args&... args ) {
		Format( value, arg0 );
		Format<Args...>( value, args... );
	}

	template <typename T>
	static void Format ( Special& value, const T& arg0 ) {
		Format( value, static_cast<const Special&>(arg0) );
	}

	static void Format ( Special& value, const Special& arg0 ) {
		value.arf += arg0.arf;
	}

};

int main ( int argc, char* argv[] ) {
	Special type = Special::Format( 5, 0, 1.96f, 2.37 );

	std::cout << type.Get() << std::endl;
    
	return 0;
}