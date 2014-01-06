template<typename T>
auto func (T) -> decltype(func (T {}));
decltype(func (int {}));