

template<typename T>
T increment_B(T t);


unsigned b = increment_B(1u); // OK

template int increment_B(int); // Error: no definition available
