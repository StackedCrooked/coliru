#include <iostream>
#include <array>
#include <assert.h>
#include <memory>
#include <boost/mpl/range_c.hpp>
#include <boost/mpl/for_each.hpp>

struct BadParameter{};

template <size_t N>
size_t protocolInputIndex(size_t i){
    static_assert(N > 1, "memory must be greater than one");
	if(0 == i)
		throw BadParameter();
	else if(N < i)
		throw BadParameter();

	if(i == 1)
		return N;
	return i-1;
}

bool testProtocolInputIndex(){
	auto result = true;
	
	result &= (protocolInputIndex<3>(1) ==  3);
	result &= (protocolInputIndex<3>(2) ==  1);
	result &= (protocolInputIndex<3>(3) ==  2);
	result &= (protocolInputIndex<4>(2) ==  1);
	result &= (protocolInputIndex<5>(2) ==  1);
	result &= (protocolInputIndex<6>(2) ==  1);
	result &= (protocolInputIndex<6>(3) ==  2);
	result &= (protocolInputIndex<6>(6) ==  5);
	result &= (protocolInputIndex<4>(4) ==  3);

	return result;
}

template <size_t N>
bool eta(size_t i, size_t r){
	static_assert(N > 1, "memory must be greater than one");
	return r == (i%N) + 1;
}

bool testEta(){
	auto result = true;
	result &= (eta<3>(0,1) ==  true);
	result &= (eta<3>(0,2) ==  false);
	result &= (eta<3>(0,3) ==  false);
	result &= (eta<9>(0,9) ==  false);
	
	result &= (eta<3>(1,1) ==  false);
	result &= (eta<3>(1,2) ==  true);
	result &= (eta<3>(1,3) ==  false);

	result &= (eta<3>(2,1) ==  false);
	result &= (eta<3>(2,2) ==  false);
	result &= (eta<3>(2,3) ==  true);

	result &= (eta<3>(3,1) ==  true);
	result &= (eta<3>(3,2) ==  false);
	result &= (eta<3>(3,3) ==  false);

	result &= (eta<3>(4,1) ==  false);
	result &= (eta<3>(4,2) ==  true);
	result &= (eta<3>(4,3) ==  false);

	for(auto i : {6, 9, 12, 15, 18}){
		result &= (eta<3>(i,1) ==  true);
		result &= (eta<3>(i,2) ==  false);
		result &= (eta<3>(i,3) ==  false);
	}

	return result;
}

template <size_t N, typename OriginalProtocol>
using errorVector = std::array<typename OriginalProtocol::Error, N>;

template <size_t N, size_t row, typename OriginalProtocol>
typename OriginalProtocol::Error rowH(size_t i, errorVector<N, OriginalProtocol> e, typename OriginalProtocol::State x){
	static_assert(N > 1, "memory must be greater than one");
	static_assert(row >= 1, "row must be greater than one");
	static_assert(row <= N, "row must be smaller than the memory");
	if(eta<N>(i, row)){
		assert(protocolInputIndex<N>(row)-1 >= 0);
		assert(protocolInputIndex<N>(row)-1 < N);
		auto result = OriginalProtocol::h(i, e[protocolInputIndex<N>(row)-1], x);
		OriginalProtocol::setRow(result, row);
		return result;
	}

	auto result = OriginalProtocol::verbatim(i, e[row - 1]);
	OriginalProtocol::setRow(result, row);
	return result;
}

namespace Test{
	struct OriginalProtocol{
		using Error = size_t;
		using State = size_t;

		static Error h(size_t i, Error e, State x){
			return (e>0)?(e-1):e;
		}

		static Error verbatim(size_t i, Error e){
			return e;
		}

		static void setRow(Error&, size_t){
        }
	};
}

bool testRowH(){
	auto result = true;

	result &= (rowH<3, 1, Test::OriginalProtocol>(0, {0, 0, 10}, 100) == 9);
	result &= (rowH<3, 2, Test::OriginalProtocol>(0, {0, 10, 0}, 100) == 10);
	result &= (rowH<3, 1, Test::OriginalProtocol>(1, {10, 0, 7}, 100) == 10);
	result &= (rowH<3, 2, Test::OriginalProtocol>(1, {10, 0, 7}, 100) == 9);
	result &= (rowH<3, 3,Test::OriginalProtocol>(1, {10, 0, 7}, 100) == 7);
	result &= (rowH<3, 1,Test::OriginalProtocol>(2, {10, 0, 0}, 100) == 10);
	result &= (rowH<3, 3,Test::OriginalProtocol>(2, {1, 2, 3}, 100) == 1);
	for(auto i : {3, 6, 9, 12, 15, 18}){
		result &= (rowH<3, 1, Test::OriginalProtocol>(i, {0, 0, 10}, 100) == 9);
	}
	return result;
}

#if 0
template <typename T, typename... Ts>
T unpack();

template <typename T>
T unpack();

template <typename... Ts>
std::array<decltype(unpack<Ts...>()), sizeof...(Ts)> ArrayInit(Ts&&... vs){
	return {vs...};
}
#endif

namespace HHelpers{
    template <size_t N, typename OriginalProtocol>
    struct Lambda
    {
        Lambda(errorVector<N, OriginalProtocol>& array_, const errorVector<N, OriginalProtocol>& e_, size_t k_, const typename OriginalProtocol::State& x_) :
            array(array_), e(e_), k(k_), x(x_) {}
        template< typename U >
        void operator()(U x)
        {
            std::get<U::value-1>(array) = rowH<N, U::value, OriginalProtocol>(k, e, x);
        }
        private:
            errorVector<N, OriginalProtocol>& array;
            errorVector<N, OriginalProtocol> e;
            size_t k;
            typename OriginalProtocol::State x;
    };
}

template <size_t N, typename OriginalProtocol>
errorVector<N, OriginalProtocol> H(size_t k, errorVector<N, OriginalProtocol> e, typename OriginalProtocol::State x){
	using returnType = errorVector<N, OriginalProtocol>;
	returnType result;

	using range = boost::mpl::range_c<size_t, 1, N+1>;
	boost::mpl::for_each<range>(
        HHelpers::Lambda<N, OriginalProtocol>(result, e, k, x)
	);

	return result;
}

bool testH(){
	auto result = true;

	result &= (H<3,Test::OriginalProtocol>(0, {1, 2, 3}, 100)[0] == 2);
	result &= (H<3,Test::OriginalProtocol>(1, {1, 2, 3}, 100)[0] == 1);
	result &= (H<3,Test::OriginalProtocol>(1, {1, 2, 3}, 100)[1] == 0);
	result &= (H<3,Test::OriginalProtocol>(2, {1, 2, 3}, 100)[0] == 1);
	result &= (H<3,Test::OriginalProtocol>(2, {1, 2, 3}, 100)[1] == 2);
	result &= (H<3,Test::OriginalProtocol>(2, {1, 2, 3}, 100)[2] == 1);
	result &= (H<3,Test::OriginalProtocol>(3, {1, 2, 3}, 100)[0] == 2);

	return result;
}

template <size_t N, typename OriginalProtocol>
errorVector<N, OriginalProtocol> evolve(size_t t0, size_t tf, errorVector<N, OriginalProtocol> e0, typename OriginalProtocol::State x){
	auto result = e0;
	for(auto i = t0; i < tf; ++i){
		result = H<N, OriginalProtocol>(i, result, x);
	}
	return result;
}

bool testEvolve(){
	auto result = true;

	result &= (evolve<3, Test::OriginalProtocol>(0, 0, {10, 9, 8}, 100)[0] == 10);
	result &= (evolve<3,Test::OriginalProtocol>(0, 0, {10, 9, 8}, 100)[1] == 9);
	result &= (evolve<3,Test::OriginalProtocol>(0, 0, {10, 9, 8}, 100)[2] == 8);

	result &= (evolve<3,Test::OriginalProtocol>(0, 3, {10, 9, 8}, 100)[1] == 6);
	result &= (evolve<3,Test::OriginalProtocol>(0, 5, {10, 9, 8}, 100)[0] == 4);
	result &= (evolve<3,Test::OriginalProtocol>(0, 8, {10, 9, 8}, 100)[1] == 0);
	result &= (evolve<3,Test::OriginalProtocol>(0, 6, {10, 9, 8}, 100)[2] == 2);
	result &= (evolve<3,Test::OriginalProtocol>(0, 1, {10, 9, 8}, 100)[2] == 8);
	result &= (evolve<3,Test::OriginalProtocol>(0, 1, {10, 9, 8}, 100)[0] == 7);
	result &= (evolve<3,Test::OriginalProtocol>(0, 8, {10, 9, 8}, 100)[0] == 1);
	result &= (evolve<3,Test::OriginalProtocol>(0, 8, {10, 9, 8}, 100)[2] == 2);

	return result;
}

struct ErrorImpl{
	size_t i = 1000;
	size_t row = 1000;
	bool protocol = false;
	std::shared_ptr<ErrorImpl> dad = nullptr;
};

template <typename OS>
OS& operator<<(OS& os, const ErrorImpl& e){
	os << "e_" << e.row << "(" << e.i << ")" << ", protocol: " << e.protocol;
	if(e.dad){
		os << std::endl;
		os << '\t' << *(e.dad);
	}
	return os;
}

struct Protocol{
	using Error = std::shared_ptr<ErrorImpl>;
	using State = size_t;

	static Error h(size_t i, const Error e, State x){
		auto result = std::make_shared<ErrorImpl>();
		result->i = i+1;
		result->protocol = true;
		result->dad = e;
		return result;
	}

	static Error verbatim(size_t i, const Error e){
		auto result = std::make_shared<ErrorImpl>();
		result->i = i+1;
		result->protocol = false;
		result->dad = e;
		return result;
	}

	static void setRow(Error& e, size_t row){
		e->row = row;
	}
};

bool testProtocolEvolve(){
	bool result = true;

	auto e0 = std::make_shared<ErrorImpl>();
	e0->i = 0;
	e0->row = 1;
	e0->protocol = false;
	auto e1 = std::make_shared<ErrorImpl>();
	e1->i = 0;
	e1->row = 2;
	e1->protocol = false;
	auto e2 = std::make_shared<ErrorImpl>();
	e2->i = 0;
	e2->row = 3;
	e2->protocol = false;

	for(unsigned int i = 0; i < 10; ++i){
		auto tmp = evolve<3, Protocol>(0, i, {e0, e1, e2}, 100);

		std::cout << *(tmp[0]) << std::endl;
		std::cout << *(tmp[1]) << std::endl;
		std::cout << *(tmp[2]) << std::endl;
		std::cout << std::endl;
	}

	return result;
}

int main(){
	assert(testProtocolInputIndex());
	assert(testEta());
	assert(testRowH());
	assert(testH());
	assert(testEvolve());
	assert(testProtocolEvolve());
	return 0;
}
