#include <memory>
#include <iostream>

#include <Furrovine++/Vector3.h>
#include "real.h"

struct sphere_arg_t { };
const auto sphere_arg = sphere_arg_t{ };
struct plane_arg_t { };
const auto plane_arg = plane_arg_t{ };
struct triangle_arg_t { };
const auto triangle_arg = triangle_arg_t{ };

enum class PrimitiveId {
    Sphere,
	Triangle,
	Plane
};

template <typename T>
struct TPrimitive {
	PrimitiveId id;
	union {
		struct {
			T radius;
			RVector3<T> position;
		} sphere;
		struct {
			T distance;
			RVector3<T> normal;
		} plane;
		struct {
			RVector3<T> a, b, c;
		} triangle;
	};

	TPrimitive( sphere_arg_t, T radius, const RVector3<T>& position ) : id( PrimitiveId::Sphere ), radius( radius ), position( position ) {

	}

	TPrimitive( plane_arg_t, T distance, const RVector3<T>& normal ) : id( PrimitiveId::Plane ), distance( distance ), normal( normal ) {

	}

	TPrimitive( triangle_arg_t, const RVector3<T>& a, const RVector3<T>& b, const RVector3<T>& c ) : id( PrimitiveId::Triangle ), a( a ), b( b ), c( c ) {

	}

};

typedef TPrimitive<real> Primitive;


int main()
{
    std::unique_ptr<int> arf;
    std::cout << std::boolalpha << ( arf == nullptr ) << std::endl;
}
