
      // _GLIBCXX_RESOLVE_LIB_DEFECTS
      // 438. Ambiguity in the "do the right thing" clause
      template<typename _Integer>
        void
        _M_initialize_dispatch(_Integer __n, _Integer __value, __true_type)
        {
      this->_M_impl._M_start = _M_allocate(static_cast<size_type>(__n));
	  this->_M_impl._M_end_of_storage =
	    this->_M_impl._M_start + static_cast<size_type>(__n);
	  _M_fill_initialize(static_cast<size_type>(__n), __value);
	}

      // Called by the range constructor to implement [23.1.1]/9
      template<typename _InputIterator>
        void
        _M_initialize_dispatch(_InputIterator __first, _InputIterator __last,
			       __false_type)
        {
	  typedef typename std::iterator_traits<_InputIterator>::
	    iterator_category _IterCategory;
	  _M_range_initialize(__first, __last, _IterCategory());
	}
    
    
      template<typename _InputIterator>
        vector(_InputIterator __first, _InputIterator __last,
           const allocator_type& __a = allocator_type())
	: _Base(__a)
        {
	  // Check whether it's an integral type.  If so, it's not an iterator.
	  typedef typename std::__is_integer<_InputIterator>::__type _Integral;
	  _M_initialize_dispatch(__first, __last, _Integral());
	}