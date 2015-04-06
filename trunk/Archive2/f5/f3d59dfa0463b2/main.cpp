template<typename T, std::size_t tag, typename = typename std::enable_if<std::is_convertible<ComponentType, T>::value>::type>
operator Coord<T, tag>() {
    return Coord<T, tag>(x, y, z);
}