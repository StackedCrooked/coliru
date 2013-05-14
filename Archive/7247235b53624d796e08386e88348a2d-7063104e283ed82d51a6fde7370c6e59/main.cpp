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

			TR operator () ( Tn&&... argn ) {
				return next( fx( std::forward<Tn>( argn )... ) );
			}
		};

		template <typename TFx, typename ...TFxn>
		struct fchain<1, TFx, TFxn...> {
			typedef typename std::result_of< TFx( Tn... ) >::type TResult;
			TFx fx;

			fchain ( TFx&& fx, TFxn&&... fxn ) : fx( std::forward<TFx>( fx ) ) {

			}

			TR operator () ( Tn&&... argn ) {
				return fx( std::forward<Tn>( argn )... );
			}
		};

		template <typename ...TFxn>
		struct fchain<0, TFxn...> {
			typedef TR TResult;

			fchain ( TFxn&&... ) {

			}

			TR operator () ( Tn&&... argn ) {
				return TR();
			}
		};

		template <ulword n, typename Ti, typename TFx, typename ... TFxn>
		struct flink<n, Ti, TFx, TFxn...> {
			typedef typename std::result_of< TFx( Ti ) >::type TResult;
			TFx fx;
			flink<n - 1, TResult, TFxn...> next;

			flink ( TFx&& fx, TFxn&&... fxn ) : fx( std::forward<TFx>( fx ) ), next( std::forward<TFxn>( fxn )... ) {

			}

			TR operator () ( Ti&& argi ) {
				return next( fx( std::forward<Ti>( argi ) ) );
			}

		};

		template <ulword n, typename TFx, typename ... TFxn>
		struct flink<n, void, TFx, TFxn...> {
			typedef typename std::result_of< TFx( ) >::type TResult;
			TFx fx;
			flink<n - 1, TResult, TFxn...> next;

			flink ( TFx&& fx, TFxn&&... fxn ) : fx( std::forward<TFx>( fx ) ), next( std::forward<TFxn>( fxn )... ) {

			}

			TR operator () ( ) {
				fx( );
				return next(  );
			}

		};

		template <typename Ti, typename TFx>
		struct flink <1, Ti, TFx> {
			typedef typename std::result_of< TFx( Ti ) >::type TResult;
			TFx fx;

			flink ( TFx&& fx ) : fx( std::forward<TFx>( fx ) ) {

			}

			TR operator () ( Ti&& argi ) {
				return fx( std::forward<Ti>( argi ) );
			}

		};

		template <typename TFx>
		struct flink <1, void, TFx> {
			typedef typename std::result_of< TFx( ) >::type TResult;
			TFx fx;

			flink ( TFx&& fx ) : fx( std::forward<TFx>( fx ) ) {

			}

			TR operator () ( ) {
				fx( );
			}

		};

	private:
		typedef std::function<TR( Tn...)> TFunction;
		TFunction chainbegin;

	public:

		template <typename ...TFxn> 
		explicit functor_chain ( TFxn&&... fxn ) : chainbegin( fchain<sizeof...( TFxn ), TFxn...>( std::forward<TFxn>( fxn )... ) ) {

		}

		functor_chain ( const functor_chain& copy ) : chainbegin( copy.chainbegin ) {

		}

		functor_chain ( functor_chain&& mov ) : chainbegin(std::move(mov.chainbegin)) {

		}

		functor_chain& operator= ( const functor_chain& copy ) {
			chainbegin = copy.chainbegin;
			return *this;
		}

		functor_chain& operator= ( functor_chain&& mov ) {
			chainbegin = std::move(mov.chainbegin);
			return *this;
		}

		template <typename ...TFxn> 
		void reset ( TFxn&&... fxn ) {
			chainbegin = TFunction( fchain<sizeof...( TFxn ), TFxn...>( std::forward<TFxn>( fxn )... ) );
		}

		TR operator () ( Tn&&... argn ) {
			return chainbegin( std::forward<Tn>( argn ) ... );
		}

		template <typename... TKickn>
		TR operator () ( TKickn&&... argn ) {
			return chainbegin( std::forward<TKickn>( argn ) ... );
		}

	};

	template <typename TR>
	struct functor_chain<TR, void> {
	private:

		template <ulword n, typename Ti, typename ...TFxn>
		struct flink;

		template <ulword n, typename ...TFxn>
		struct fchain;

		template <ulword n, typename TFx, typename ...TFxn>
		struct fchain<n, TFx, TFxn...> {
			typedef typename std::result_of< TFx( ) >::type TResult;
			TFx fx;
			flink<n - 1, TResult, TFxn...> next;

			fchain ( TFx&& fx, TFxn&&... fxn ) : fx( std::forward<TFx>( fx ) ), next( std::forward<TFxn>( fxn )... ) {

			}

			TR operator () ( ) {
				return next( fx( ) );
			}
		};

		template <typename TFx, typename ...TFxn>
		struct fchain<1, TFx, TFxn...> {
			typedef typename std::result_of< TFx( ) >::type TResult;
			TFx fx;

			fchain ( TFx&& fx, TFxn&&... fxn ) : fx( std::forward<TFx>( fx ) ) {

			}

			TR operator () ( ) {
				return fx( );
			}
		};

		template <typename ...TFxn>
		struct fchain<0, TFxn...> {
			typedef TR TResult;

			fchain ( TFxn&&... ) {

			}

			TR operator () ( ) {
				return TR();
			}
		};

		template <ulword n, typename Ti, typename TFx, typename ... TFxn>
		struct flink<n, Ti, TFx, TFxn...> {
			typedef typename std::result_of< TFx( Ti ) >::type TResult;
			TFx fx;
			flink<n - 1, TResult, TFxn...> next;

			flink ( TFx&& fx, TFxn&&... fxn ) : fx( std::forward<TFx>( fx ) ), next( std::forward<TFxn>( fxn )... ) {

			}

			TR operator () ( Ti&& argi ) {
				return next( fx( std::forward<Ti>( argi ) ) );
			}

		};

		template <ulword n, typename TFx, typename ... TFxn>
		struct flink<n, void, TFx, TFxn...> {
			typedef typename std::result_of< TFx( ) >::type TResult;
			TFx fx;
			flink<n - 1, TResult, TFxn...> next;

			flink ( TFx&& fx, TFxn&&... fxn ) : fx( std::forward<TFx>( fx ) ), next( std::forward<TFxn>( fxn )... ) {

			}

			TR operator () ( ) {
				fx( );
				return next(  );
			}

		};

		template <typename Ti, typename TFx>
		struct flink <1, Ti, TFx> {
			typedef typename std::result_of< TFx( Ti ) >::type TResult;
			TFx fx;

			flink ( TFx&& fx ) : fx( std::forward<TFx>( fx ) ) {

			}

			TR operator () ( Ti&& argi ) {
				return fx( std::forward<Ti>( argi ) );
			}

		};

		template <typename TFx>
		struct flink <1, void, TFx> {
			typedef typename std::result_of< TFx( ) >::type TResult;
			TFx fx;

			flink ( TFx&& fx ) : fx( std::forward<TFx>( fx ) ) {

			}

			TR operator () ( ) {
				fx( );
			}

		};

	private:
		std::function<TR( )> chainbegin;

	public:

		template <typename ...TFxn> 
		explicit functor_chain ( TFxn&&... fxn ) : chainbegin( fchain<sizeof...( TFxn ), TFxn...>( std::forward<TFxn>( fxn )... ) ) {

		}

		functor_chain ( const functor_chain& copy ) : chainbegin( copy.chainbegin ) {

		}

		functor_chain ( functor_chain&& mov ) : chainbegin(std::move(mov.chainbegin)) {

		}

		functor_chain& operator= ( const functor_chain& copy ) {
			chainbegin = copy.chainbegin;
			return *this;
		}

		functor_chain& operator= ( functor_chain&& mov ) {
			chainbegin = std::move(mov.chainbegin);
			return *this;
		}

		template <typename ...TFxn> 
		void reset ( TFxn&&... fxn ) {
			chainbegin = TFunction( fchain<sizeof...( TFxn ), TFxn...>( std::forward<TFxn>( fxn )... ) );
		}

		TR operator () ( ) {
			return chainbegin( );
		}

	};

	template <>
	struct functor_chain<void> {
	private:

		template <ulword n, typename Ti, typename ...TFxn>
		struct flink;

		template <ulword n, typename ...TFxn>
		struct fchain;

		template <ulword n, typename TFx, typename ...TFxn>
		struct fchain<n, TFx, TFxn...> {
			typedef typename std::result_of< TFx( ) >::type TResult;
			TFx fx;
			flink<n - 1, TResult, TFxn...> next;

			fchain ( TFx&& fx, TFxn&&... fxn ) : fx( std::forward<TFx>( fx ) ), next( std::forward<TFxn>( fxn )... ) {

			}

			void operator () ( ) {
				fx( );
				return next(  );
			}
		};

		template <typename TFx, typename ...TFxn>
		struct fchain<1, TFx, TFxn...> {
			typedef typename std::result_of< TFx( ) >::type TResult;
			TFx fx;

			fchain ( TFx&& fx, TFxn&&... fxn ) : fx( std::forward<TFx>( fx ) ) {

			}

			void operator () ( ) {
				return fx( );
			}
		};

		template <typename ...TFxn>
		struct fchain<0, TFxn...> {
			
			fchain ( TFxn&&... ) {

			}

			void operator () ( ) {
				return ;
			}
		};

		template <ulword n, typename Ti, typename TFx, typename ... TFxn>
		struct flink<n, Ti, TFx, TFxn...> {
			typedef typename std::result_of< TFx( Ti ) >::type TResult;
			TFx fx;
			flink<n - 1, TResult, TFxn...> next;

			flink ( TFx&& fx, TFxn&&... fxn ) : fx( std::forward<TFx>( fx ) ), next( std::forward<TFxn>( fxn )... ) {

			}

			void operator () ( Ti&& argi ) {
				return next( fx( std::forward<Ti>( argi ) ) );
			}

		};

		template <ulword n, typename TFx, typename ... TFxn>
		struct flink<n, void, TFx, TFxn...> {
			typedef typename std::result_of< TFx( ) >::type TResult;
			TFx fx;
			flink<n - 1, TResult, TFxn...> next;

			flink ( TFx&& fx, TFxn&&... fxn ) : fx( std::forward<TFx>( fx ) ), next( std::forward<TFxn>( fxn )... ) {

			}

			void operator () ( ) {
				fx( );
				return next(  );
			}

		};

		template <typename Ti, typename TFx>
		struct flink <1, Ti, TFx> {
			typedef typename std::result_of< TFx( Ti ) >::type TResult;
			TFx fx;

			flink ( TFx&& fx ) : fx( std::forward<TFx>( fx ) ) {

			}

			void operator () ( Ti&& argi ) {
				return fx( std::forward<Ti>( argi ) );
			}

		};

		template <typename TFx>
		struct flink <1, void, TFx> {
			typedef typename std::result_of< TFx( ) >::type TResult;
			TFx fx;

			flink ( TFx&& fx ) : fx( std::forward<TFx>( fx ) ) {

			}

			void operator () ( ) {
				fx( );
			}

		};

	private:
		std::function<void( )> chainbegin;

	public:

		template <typename ...TFxn> 
		explicit functor_chain ( TFxn&&... fxn ) : chainbegin( fchain<sizeof...( TFxn ), TFxn...>( std::forward<TFxn>( fxn )... ) ) {

		}

		functor_chain ( const functor_chain& copy ) : chainbegin( copy.chainbegin ) {

		}

		functor_chain ( functor_chain&& mov ) : chainbegin(std::move(mov.chainbegin)) {

		}

		functor_chain& operator= ( const functor_chain& copy ) {
			chainbegin = copy.chainbegin;
			return *this;
		}

		functor_chain& operator= ( functor_chain&& mov ) {
			chainbegin = std::move(mov.chainbegin);
			return *this;
		}

		template <typename ...TFxn> 
		void reset ( TFxn&&... fxn ) {
			chainbegin = TFunction( fchain<sizeof...( TFxn ), TFxn...>( std::forward<TFxn>( fxn )... ) );
		}

		void operator () ( ) {
			return chainbegin( );
		}

	};

	template <typename TR, typename ...Tn, typename ...TFxn>
	functor_chain<TR, Tn...> make_chain ( TFxn&&... fxn ) {
		return functor_chain<TR, Tn...>( std::forward<TFxn>( fxn )... );
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

struct das_float {

    int operator () ( float num ) {
		return (int)num;
	}

};

struct xBlank {

    void operator () () {
		std::cout << "And nothing happened!" << std::endl;
	}

};

int main ( int argc, char** argv ) {
	
auto mul2 = x2();
    auto mul3 = x3();
	auto x = []( int x ){ return x + 100; };
	functor_chain<int, int> chain( mul2, mul3, x );
	int result = 2;
	std::cout << "Before: " << result << std::endl;
	result = chain( result );
	std::cout << "After:  " << result << std::endl;

	chain.reset( mul2, mul3, mul2, x );
	result = 2;
	std::cout << "Before: " << result << std::endl;
	result = chain( result );
	std::cout << "After:  " << result << std::endl;

	functor_chain<int, int> emptychain;
	std::cout << "Before: " << result << std::endl;
	result = emptychain( result );
	std::cout << "After:  " << result << std::endl;

	functor_chain<void, int> voidchain = functor_chain<void, int>( x2(), xBlackhole() );
	std::cout << "Before: " << result << std::endl;
	voidchain( result );
	std::cout << "After:  " << result << std::endl;

	float fresult = 5.5f;
	functor_chain<void, float> voidfchain = functor_chain<void, float>( das_float(), x2(), xBlackhole() );
	std::cout << "Before: " << fresult << std::endl;
	voidfchain( fresult );
	std::cout << "After:  " << fresult << std::endl;
	
	functor_chain<void> voidvoidchain = functor_chain<void>( xBlank(), xBlank() );
	voidvoidchain( );
}