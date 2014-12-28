unordered_set<signed long long> getValues(unordered_set<signed long long> contents, char buffer[102400])
{
    unordered_set<signed long long> returnValue; //+4, -32, +52, so on..
	auto oldit = contents.begin(); //The last position of the iterator

	for (int i = 0; i < 102400; i++)
	{
		auto it = contents.find(buffer[i]); //Set iterator to position of the next byte
		auto diff = distance(it, oldit); //Get the difference (+3, -12, so on)
		returnValue.insert(diff); //Insert that difference into the return value
		oldit = it; //Set the old iterator to the current iterator for the next loop.'
	}

	return returnValue;
}