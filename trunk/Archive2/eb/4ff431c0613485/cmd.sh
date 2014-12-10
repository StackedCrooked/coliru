ln -s /Archive2/2e/e552c776bbfc98/main.cpp variant_fwd.hpp
ln -s /Archive2/f8/03d7b21e7b4e56/main.cpp recursive_wrapper.hpp
ln -s /Archive2/09/cc89159803cf50/main.cpp traits.hpp
ln -s /Archive2/23/baf93cc309abc1/main.cpp variant.hpp
ln -s /Archive2/af/3cff677c80d53b/main.cpp visitor.hpp
time g++ -DBOOST_VARAINT_MAX_MULTIVIZITOR_PARAMS=6 -std=c++1y -Ofast -Wall -Wextra -pedantic -pthread main.cpp -o variant && ./variant