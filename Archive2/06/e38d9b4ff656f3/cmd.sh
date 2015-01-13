ln -s /Archive2/85/77c19e42c66e19/main.cpp traits.hpp
ln -s main.cpp recursive_wrapper.hpp
clang++ -stdlib=libc++ -std=gnu++1z -Ofast -Wall -Wextra -Weverything -pedantic -Wno-c++98-compat recursive_wrapper.hpp -fsyntax-only