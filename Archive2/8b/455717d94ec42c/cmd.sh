ln -s /Archive2/85/77c19e42c66e19/main.cpp traits.hpp
ln -s /Archive2/06/e38d9b4ff656f3/main.cpp recursive_wrapper.hpp
ln -s main.cpp variant.hpp
clang++ -stdlib=libc++ -std=gnu++1z -Ofast -Wall -Wextra -Weverything -pedantic -Wno-c++98-compat variant.hpp -fsyntax-only