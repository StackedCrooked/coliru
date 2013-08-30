    template<typename Iterator, typename Delimiter>
	std::string rangeToString(Iterator begin, Iterator end, Delimiter prefix, Delimiter suffix, Delimiter separator)
	{
		std::stringstream ss;

		ss << prefix;
		for(auto it = begin; it != end; it++)
		{
			ss << *it;

			auto next = it + 1;
			if(next != end)
				ss << separator;
		}
		ss << suffix;

		return ss.str();
	}