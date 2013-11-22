#include <iostream>
#include <stdexcept>
#include <cmath>
#include <tuple>

struct Aiming {
    enum Direction {
		N = 1u << 1u, S = 1u << 2u
		, E = 1u << 3u, W = 1u << 4u
		, NE = N | E, NW = N | W
		, SE = S | E, SW = S | W
	};
	Aiming( float angleHorizontal, float angleVertical ) {
		const float PI_2 = 3.1415f / 2.f;
		if ( angleHorizontal > angleVertical )
			throw std::logic_error( "horizontal angle must be lower than vertical angle" );
		if ( angleHorizontal >= PI_2 || angleVertical >= PI_2 )
			throw std::logic_error( "angles must be bellow pi/2" );

		// the logic behind the thing
		// tan a < tan (a + epsilon)
		// tan = sin / cos
		// cos*tan = sin

		// tan a > tan v 
		// sin a / cos a > tan v
		// sin a > tan v * cos a : this is the condition to be vertical only
		// sin a < tan v * cos a : this is the condition to be horizontal only

		auto angle2Factors = [] ( float angle ) -> std::pair<int, int> {
			float const scale = 8192; // just to keep precision in integer with angles near 0 and pi/2
			float tan = std::tan( angle );
			if ( tan > 1.f )
				return std::make_pair( int( tan * scale ), int( scale ) );
			else
				return std::make_pair( int( scale ), int( scale / tan ) );
		};

		std::tie( factorCosVert_, factorSinVert_ ) = angle2Factors( angleVertical );
		std::tie( factorCosHor_, factorSinHor_ ) = angle2Factors( angleHorizontal );

		//std::cout << factorCosVert_ << " " << factorSinVert_ << std::endl;
		//std::cout << factorCosHor_ << " " <<  factorSinHor_ << std::endl;
	}

	Direction operator()( int mouseX, int mouseY ) const {
		int relativeX = mouseX - originX_;
		int relativeY = mouseY - originY_;

		Direction hor = relativeX > 0 ? Direction::E : Direction::W;
		Direction ver = relativeY > 0 ? Direction::S : Direction::N;

		int absX = std::abs( relativeX ); // is unormalized cosinus
		int absY = std::abs( relativeY ); // is unormalized sinus

		if ( absX * factorCosVert_ < absY * factorSinVert_ ) {
			return ver;
		} else if ( absX * factorCosHor_ > absY * factorSinHor_ ) {
			return hor;
		}
		return Direction( hor | ver );
	}
private:
	int originX_ {}; // to init with the window mouse center coordinate
	int originY_ {}; // to init with the window mouse center coordinate
	int factorCosVert_;
	int factorSinVert_;
	int factorCosHor_;
	int factorSinHor_;
};

std::ostream& operator<<( std::ostream& os, Aiming::Direction d ) {
	switch ( d ) {
	case Aiming::N: os << "N"; break;
	case Aiming::S: os << "S"; break;
	case Aiming::E: os << "E"; break;
	case Aiming::W: os << "W"; break;
	case Aiming::NE: os << "NE"; break;
	case Aiming::NW: os << "NW"; break;
	case Aiming::SE: os << "SE"; break;
	case Aiming::SW: os << "SW"; break;
	};
	return os;
}

void testAim( float h, float v ) {
	std::cout << "H = " << h << "deg; V = " << v << "deg" << std::endl;
	auto deg2rad = [] ( float deg ) { return deg * 3.1415f / 180.f; };
	Aiming aim { deg2rad( h ), deg2rad( v ) };

	auto dir = [ = ] ( int a ) { return aim( 500.f * std::cos( deg2rad( a ) ), -500.f * std::sin( deg2rad( a ) ) ); };

	for ( int a = 0; a < 360; ) {
		auto val = dir(a);
		int start = a++;
		while ( a < 360 && dir(a) == val ) {
			a++;
		}
		std::cout << "[" << start << ".." << a << "[ = " << val << "; ";
	}
	std::cout << std::endl;
}
int main( ) {
	auto deg2rad = [] ( float deg ) { return deg * 3.1415f / 180.f; };
	Aiming aim { deg2rad( 29.9f ), deg2rad( 40.f ) };

	testAim( 29.9f, 40.f );

	testAim( 60.f, 80.f );
	testAim( 35.f, 55.f );

	return 0;
}