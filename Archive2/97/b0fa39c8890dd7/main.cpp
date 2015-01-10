#include <array>
#include <type_traits>

#include <iostream>
#include <typeinfo>

template<class ElementT, unsigned int Dimensions>
class Vector
{
public:

	typedef std::array<ElementT, Dimensions> DataT;

	Vector():
		data() { }

	explicit Vector(std::initializer_list<ElementT> values):
		data()
	{
		std::copy(values.begin(), values.end(), data.begin());
	}

	template<class E>
	explicit Vector(Vector<E, Dimensions> const& other):
		data()
	{
		std::copy(other.Data().begin(), other.Data().end(), data.begin());
	}

	Vector& operator*=(ElementT value)
	{
		for (auto& e : data)
			e *= value;

		return *this;
	}

	Vector& operator*=(Vector const& other)
	{
		for (auto i = 0u; i != data.size(); ++i)
			data[i] *= other.data[i];

		return *this;
	}

	// etc. ...

	template<class E>
	operator Vector<E, Dimensions>() const
	{
		return Vector<E, Dimensions>(*this);
	}


	DataT& Data()
	{
		return data;
	}

	DataT const& Data() const
	{
		return data;
	}

private:

	friend std::ostream& operator<<(std::ostream& stream, Vector v)
	{
		for (auto const& e : v.data)
			stream << e << " ";

		return stream;
	}

	DataT data;
};

template<class E, class T, unsigned int D, class R = std::common_type_t<E, T>>
Vector<R, D> operator*(Vector<E, D> v, T value)
{
	auto result = Vector<R, D>(v);
	result *= value;

	return result;
}

template<class E, class T, unsigned int D, class R = std::common_type_t<E, T>>
Vector<R, D> operator*(T value, Vector<E, D> const& v)
{
	auto result = Vector<R, D>(v);
	result *= value;

	return result;
}

template<class E1, class E2, unsigned int D, class R = std::common_type_t<E1, E2>>
Vector<R, D> operator*(Vector<E1, D> const& v1, Vector<E2, D> const& v2)
{
	auto result = Vector<R, D>(v1);
	result *= v2;

	return result;
}

void TestVector()
{
	std::cout << "Testing Vector" << std::endl;

	using Vec3 = Vector<float, 3u>;

	// This is the behaviour I would like:
	//{
	//	auto f = 1.f;
	//	auto d = 2.0;

	//	f *= d; // warns about possible loss of data
	//	d *= f; // fine

	//	auto d2 = f * d; // fine (f promotion)
	//}

	// Same types. All fine.
	{
		auto v1 = Vec3({ 1, 2, 3 });
		auto v2 = Vec3({ 1, 2, 3 });

		v1 *= 2.f;
		v1 *= v2;

		std::cout << v1 << std::endl;
	}

	{
		auto v1 = Vec3({ 1, 2, 3 });
		auto v2 = Vec3({ 1, 2, 3 });

		std::cout << (v1 * 2.f) << std::endl;
		std::cout << (v1 * v2) << std::endl;
	}

	{
		auto v1 = Vector<float, 3u>({ 1, 2, 3 });
		auto v2 = Vector<double, 3u>({ 1, 2, 3 });

		v1 *= 2.0; // why no warning here? :(
		v1 *= v2; // produces warning :)

		v2 *= v1; // no warning :)

		std::cout << v1 << std::endl;
	}

	{
		auto v1 = Vector<float, 3u>({ 1, 2, 3 });
		auto v2 = v1 * 2.0;
		auto v3 = v1 * v2; // v1 promotion -> should create another Vector<double, 3u> 
		auto v4 = 2.0 * v1;
		
		std::cout << v2 << " " << typeid(v2).name() << std::endl;
		std::cout << v3 << " " << typeid(v3).name() << std::endl;
		std::cout << v4 << " " << typeid(v4).name() << std::endl;
	}
}

int main()
{
    TestVector();
}
