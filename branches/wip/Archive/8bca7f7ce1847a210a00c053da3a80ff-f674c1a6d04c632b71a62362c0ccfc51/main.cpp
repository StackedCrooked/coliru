template<class _FwdIt> inline
    pair<_FwdIt, _FwdIt>
		_Minmax_element(_FwdIt _First, _FwdIt _Last)
	{	// find smallest and largest elements, using operator<
	pair<_FwdIt, _FwdIt> _Found(_First, _First);

	if (_First != _Last)
		for (; ++_First != _Last; )
			{	// process one or two elements
			_FwdIt _Next = _First;
			if (++_Next == _Last)
				{	// process last element
				if (_DEBUG_LT(*_First, *_Found.first))
					_Found.first = _First;
				else if (_DEBUG_LT(*_Found.second, *_First))
					_Found.second = _First;
				}
			else
				{	// process next two elements
				if (_DEBUG_LT(*_Next, *_First))
					{	// test _Next for new smallest
					if (_DEBUG_LT(*_Next, *_Found.first))
						_Found.first = _Next;
					if (_DEBUG_LT(*_Found.second, *_First))
						_Found.second = _First;
					}
				else
					{	// test _First for new smallest
					if (_DEBUG_LT(*_First, *_Found.first))
						_Found.first = _First;
					if (_DEBUG_LT(*_Found.second, *_Next))
						_Found.second = _Next;
					}
				_First = _Next;
				}
			}
	return (_Found);
	}