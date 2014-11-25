#include <utility>
#include <map>
#include <iterator>
#include <tuple>
#include <vector>
#include <string>
#include <iostream>

        // a little library to detect iterability, and tuple-ness:
        namespace details {
    		using std::begin; using std::end;
			template<class T, class=void>
			struct is_iterable_test:std::false_type{};
			template<class T>
			struct is_iterable_test<T,
				decltype((void)(
					(void)(begin(std::declval<T>())==end(std::declval<T>()))
					, ((void)(std::next(begin(std::declval<T>()))))
					, ((void)(*begin(std::declval<T>())))
                    , 1
				))
			>:std::true_type{};
			template<class T>struct is_tupleoid:std::false_type{};
			template<class...Ts>struct is_tupleoid<std::tuple<Ts...>>:std::true_type{};
			template<class...Ts>struct is_tupleoid<std::pair<Ts...>>:std::true_type{};
			// template<class T, size_t N>struct is_tupleoid<std::array<T,N>>:std::true_type{}; // complete, but problematic
		}
		template<class T>struct is_iterable:details::is_iterable_test<std::decay_t<T>>{};
    	template<class T, std::size_t N>struct is_iterable<T(&)[N]>:std::true_type{}; // bypass decay
		template<class T>struct is_tupleoid:details::is_tupleoid<std::decay_t<T>>{};
        
		template<class T>struct is_visitable:std::integral_constant<bool, is_iterable<T>{}||is_tupleoid<T>{}> {};

        // a library that lets us visit the contents of an iterable or tuple type object:
        template<class C, class F>
		std::enable_if_t<is_iterable<C>{}> visit_first(C&& c, F&& f) {
			using std::begin; using std::end;
			auto&& b = begin(c);
			auto&& e = end(c);
			if (b==e)
					return;
			std::forward<F>(f)(*b);
		}
        template<class C, class F>
		std::enable_if_t<is_iterable<C>{}> visit_all_but_first(C&& c, F&& f) {
			using std::begin; using std::end;
			auto it = begin(c);
			auto&& e = end(c);
			if (it==e)
					return;
			it = std::next(it);
			for( ; it!=e; it = std::next(it) ) {
				f(*it);
			}
		}

		namespace details {
			template<class Tup, class F>
			void visit_first( std::index_sequence<>, Tup&&, F&& ) {}
			template<size_t... Is, class Tup, class F>
			void visit_first( std::index_sequence<0,Is...>, Tup&& tup, F&& f ) {
				std::forward<F>(f)( std::get<0>( std::forward<Tup>(tup) ) );
			}
			template<class Tup, class F>
			void visit_all_but_first( std::index_sequence<>, Tup&&, F&& ) {}
			template<size_t... Is,class Tup, class F>
			void visit_all_but_first( std::index_sequence<0,Is...>, Tup&& tup, F&& f ) {
				int unused[] = {0,((void)(
					f( std::get<Is>(std::forward<Tup>(tup)) )
				),0)...};
				(void)(unused);
			}
		}
        template<class Tup, class F>
		std::enable_if_t<is_tupleoid<Tup>{}> visit_first(Tup&& tup, F&& f) {
			details::visit_first( std::make_index_sequence< std::tuple_size<std::decay_t<Tup>>{} >{}, std::forward<Tup>(tup), std::forward<F>(f) );
		}
        template<class Tup, class F>
		std::enable_if_t<is_tupleoid<Tup>{}> visit_all_but_first(Tup&& tup, F&& f) {
			details::visit_all_but_first( std::make_index_sequence< std::tuple_size<std::decay_t<Tup>>{} >{}, std::forward<Tup>(tup), std::forward<F>(f) );
		}

        // a pretty printing library:
		namespace pretty_print {
        	namespace decorator {
	    		struct default_tag {};
                template<class Old>
		    	struct map_magic_tag:Old {}; // magic for maps

                // Maps get {}s.  Write trait `is_associative` to generalize:
    			template<class CharT, class Traits, class...Xs >
	    		void pretty_print_before( default_tag, std::basic_ostream<CharT, Traits>& s, std::map<Xs...> const& ) {
		    		s << CharT('{');
			    }

			    template<class CharT, class Traits, class...Xs >
			    void pretty_print_after( default_tag, std::basic_ostream<CharT, Traits>& s, std::map<Xs...> const& ) {
				    s << CharT('}');
			    }

                // tuples and pairs get ():
        		template<class CharT, class Traits, class Tup >
	    		std::enable_if_t<is_tupleoid<Tup>{}> pretty_print_before( default_tag, std::basic_ostream<CharT, Traits>& s, Tup const& ) {
		    		s << CharT('(');
			    }

            	template<class CharT, class Traits, class Tup >
	    		std::enable_if_t<is_tupleoid<Tup>{}> pretty_print_after( default_tag, std::basic_ostream<CharT, Traits>& s, Tup const& ) {
		    		s << CharT(')');
			    }

                // strings with the same character type get ""s:
        		template<class CharT, class Traits, class...Xs >
	    		void pretty_print_before( default_tag, std::basic_ostream<CharT, Traits>& s, std::basic_string<CharT, Xs...> const& ) {
		    		s << CharT('"');
			    }
			    template<class CharT, class Traits, class...Xs >
			    void pretty_print_after( default_tag, std::basic_ostream<CharT, Traits>& s, std::basic_string<CharT, Xs...> const& ) {
				    s << CharT('"');
			    }
                // and pack the characters together:
    		    template<class CharT, class Traits, class...Xs >
			    void pretty_print_between( default_tag, std::basic_ostream<CharT, Traits>&, std::basic_string<CharT, Xs...> const& ) {}

                // map magic.  When iterating over the contents of a map, use the map_magic_tag:
    			template<class...Xs>
	    		map_magic_tag<default_tag> pretty_print_descend( default_tag, std::map<Xs...> const& ) {
                    return {};
                }
		    	template<class old_tag, class C>
			    old_tag pretty_print_descend( map_magic_tag<old_tag>, C const& ) {
                    return {};
                }

                // When printing a pair immediately within a map, use -> as a separator:
			    template<class old_tag, class CharT, class Traits, class...Xs >
			    void pretty_print_between( map_magic_tag<old_tag>, std::basic_ostream<CharT, Traits>& s, std::pair<Xs...> const& ) {
				    s << CharT('-') << CharT('>');
			    }
		    }
            // default behavior:
			template<class CharT, class Traits, class Tag,  class Container >
			void pretty_print_before( Tag const&, std::basic_ostream<CharT, Traits>& s, Container const& ) {
				s << CharT('[');
			}
			template<class CharT, class Traits, class Tag,  class Container >
			void pretty_print_after( Tag const&, std::basic_ostream<CharT, Traits>& s, Container const& ) {
				s << CharT(']');
			}
			template<class CharT, class Traits, class Tag,  class Container >
			void pretty_print_between( Tag const&, std::basic_ostream<CharT, Traits>& s, Container const& ) {
				s << CharT(',');
			}
			template<class Tag, class Container>
			Tag&& pretty_print_descend( Tag&& tag, Container const& ) {
				return std::forward<Tag>(tag);
			}

            // print things by default by using <<:
    		template<class Tag=decorator::default_tag, class Scalar, class CharT, class Traits>
	    	std::enable_if_t<!is_visitable<Scalar>{}> print( std::basic_ostream<CharT, Traits>& os, Scalar&& scalar, Tag&&=Tag{} ) {
		    	os << std::forward<Scalar>(scalar);
		    }
            // for anything visitable (see above), use the pretty print algorithm:
		    template<class Tag=decorator::default_tag, class C, class CharT, class Traits>
		    std::enable_if_t<is_visitable<C>{}> print( std::basic_ostream<CharT, Traits>& os, C&& c, Tag&& tag=Tag{} ) {
    			pretty_print_before( std::forward<Tag>(tag), os, std::forward<C>(c) );
	    		visit_first( c, [&](auto&& elem) {
		    		print( os, std::forward<decltype(elem)>(elem), pretty_print_descend( std::forward<Tag>(tag), std::forward<C>(c) ) );
    			});
	    		visit_all_but_first( c, [&](auto&& elem) {
		    		pretty_print_between( std::forward<Tag>(tag), os, std::forward<C>(c) );
			    	print( os, std::forward<decltype(elem)>(elem), pretty_print_descend( std::forward<Tag>(tag), std::forward<C>(c) ) );
			    });
    			pretty_print_after( std::forward<Tag>(tag), os, std::forward<C>(c) );
	    	}
		}

       // test code:
        int main() {
            std::vector<int> x = {1,2,3};
        
            pretty_print::print( std::cout, x );
            std::cout << "\n";

            std::map< std::string, int > m;
            m["hello"] = 3;
            m["world"] = 42;
        
            pretty_print::print( std::cout, m );
            std::cout << "\n";
        }
