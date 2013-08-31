#include <iostream>
#include <tuple>
#include <utility>
#include <type_traits>
#include <functional>

typedef std::size_t ulword;

    template <typename TR, typename ...Tn>
	struct functor_chain {
	private:

		template <ulword n, typename Ti, typename ...TFxn>
		struct flink;

		template <ulword n, typename ...TFxn>
		struct fchain;

		template <ulword n, typename TFx, typename ...TFxn>
		struct fchain<n, TFx, TFxn...> {
			typedef typename std::result_of< TFx( Tn... ) >::type TResult;
			TFx fx;
			flink<n - 1, TResult, TFxn...> next;

			fchain ( TFx&& fx, TFxn&&... fxn ) : fx( std::forward<TFx>( fx ) ), next( std::forward<TFxn>( fxn )... ) {

			}

			TResult operator () ( Tn&&... argn ) {
				TResult result = fx( std::forward<Tn>( argn )... );
				return next( result );
			}
		};

		template <typename TFx, typename ...TFxn>
		struct fchain<1, TFx, TFxn...> {
			typedef typename std::result_of< TFx( Tn... ) >::type TResult;
			TFx fx;

			fchain ( TFx&& fx, TFxn&&... fxn ) : fx( std::forward<TFx>( fx ) ) {

			}

			TResult operator () ( Tn&&... argn ) {
				return fx( std::forward<Tn>( argn )... );
			}
		};

		template <typename ...TFxn>
		struct fchain<0, TFxn...> {
			typedef TR TResult;
			
			fchain ( TFxn&&... ) {

			}

			TResult operator () ( Tn&&... argn ) {
				return TResult();
			}
		};

		template <ulword n, typename Ti, typename TFx, typename ... TFxn>
		struct flink<n, Ti, TFx, TFxn...> {
			typedef typename std::result_of< TFx( Ti ) >::type TResult;
			TFx fx;
			flink<n - 1, TResult, TFxn...> next;
			
			flink ( TFx&& fx, TFxn&&... fxn ) : fx( std::forward<TFx>( fx ) ), next( std::forward<TFxn>( fxn )... ) {

			}

			TR operator () ( Ti argi ) {
				TResult result = fx( argi );
				return next( result );
			}

		};

		template <typename Ti, typename TFx>
		struct flink <1, Ti, TFx> {
			typedef typename std::result_of< TFx( Ti ) >::type TResult;
			TFx fx;

			flink ( TFx&& fx ) : fx( std::forward<TFx>( fx ) ) {

			}

			TR operator () ( Ti in ) {
				return fx( in );
			}

		};

	private:
		std::function<TR( Tn...)> chainbegin;

	public:

		template <typename ...TFxn> 
		explicit functor_chain ( TFxn&&... fxn ) {
			fchain<sizeof...( TFxn ), TFxn...> c( std::forward<TFxn>( fxn )... );
			chainbegin = c;
		}

		template <typename... TKickn>
		TR operator () ( TKickn&&... argn ) {
			return chainbegin( std::forward<TKickn>( argn ) ... );
		}

	};

    template <typename TR, typename ...Tn, typename ...TFx>
	functor_chain<TR, Tn...> make_chain ( TFx&&... fx ) {
		return functor_chain<TR, Tn...>( std::forward<TFx>( fx )... );
	}

struct x2 {

    int operator () ( int num ) {
		return num * 2;
	}

};

struct x3 {

	int operator () ( int num ) {
		return num * 3;
	}

};

struct xBlackhole {

	void operator () ( int num ) {
		
	}

};

int main ( int argc, char** argv ) {
	
	auto mul2 = x2();
	auto mul3 = x3();
	functor_chain<int, int> chain( mul2, mul3, []( int x ){ return x + 100; } );
	int result = 2;
	std::cout << "Before: " << result << std::endl;
	result = chain( result );
	std::cout << "After:  " << result << std::endl;

	functor_chain<int, int> emptychain;
	std::cout << "Before: " << result << std::endl;
	result = emptychain( result );
	std::cout << "After:  " << result << std::endl;

	functor_chain<void, int> voidchain = functor_chain<void, int>( xBlackhole() );
	std::cout << "Before: " << result << std::endl;
	voidchain( result );
	std::cout << "After:  " << result << std::endl;
}