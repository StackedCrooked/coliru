// libstdc++ :
#if __cplusplus >= 201103L
template<typename _Tp, typename _Alloc>
template<typename... _Args>
void
vector<_Tp, _Alloc>::
emplace_back(_Args&&... __args)
{
    if (this->_M_impl._M_finish != this->_M_impl._M_end_of_storage)
    {
        _Alloc_traits::construct(this->_M_impl, this->_M_impl._M_finish,
                                 std::forward<_Args>(__args)...);
        ++this->_M_impl._M_finish;
    }
    else
        _M_emplace_back_aux(std::forward<_Args>(__args)...);
}
#endif

// libc++ :
template <class _Tp, class _Allocator>
template <class... _Args>
inline _LIBCPP_INLINE_VISIBILITY
void
vector<_Tp, _Allocator>::emplace_back(_Args&&... __args)
{
    if (this->__end_ < this->__end_cap())
    {
        __annotate_increase(1);
        __alloc_traits::construct(this->__alloc(),
                                  _VSTD::__to_raw_pointer(this->__end_),
                                  _VSTD::forward<_Args>(__args)...);
        ++this->__end_;
    }
    else
        __emplace_back_slow_path(_VSTD::forward<_Args>(__args)...);
}

template <class _Tp, class _Allocator>
template <class... _Args>
void
vector<_Tp, _Allocator>::__emplace_back_slow_path(_Args&&... __args)
{
    allocator_type& __a = this->__alloc();
    __split_buffer<value_type, allocator_type&> __v(__recommend(size() + 1), size(), __a);
    //    __v.emplace_back(_VSTD::forward<_Args>(__args)...);
    __alloc_traits::construct(__a, _VSTD::__to_raw_pointer(__v.__end_), _VSTD::forward<_Args>(__args)...);
    __v.__end_++;
    __swap_out_circular_buffer(__v);
}
