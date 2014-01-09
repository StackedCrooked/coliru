template <class T>
void self_assign(T& t) noexcept(noexcept(t = t))
{ // self_assign is noexcept if and only if T::operator= is noexcept
    t = t;
}