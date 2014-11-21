    auto it = memoization.begin();
	while (it != memoization.end()){
		if (it->first.operator[](0) == state[0] && it->first.operator[](1) == state[1])
		{
		//	std::cout << "   using memo table !\n";
			return it->second;
		}
		++it;
	}
