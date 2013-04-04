g++-4.8 -std=c++11 -DUSE_EXCEPTIONS -O2 -o with_exceptions main.cpp
g++-4.8 -std=c++11 -DUSE_RETURNCODE -O2 -o with_returncode main.cpp
for i in `seq 4` ; do
  echo "$(./with_exceptions)  $(./with_returncode)"
done