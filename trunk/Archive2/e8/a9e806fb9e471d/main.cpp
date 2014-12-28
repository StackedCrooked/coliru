unordered_set<uint64_t> getValues(unordered_set<uint64_t> contents, char buffer[102400])
{
    unordered_set<uint64_t> returnValue; //+4, -32, +52, so on..
	uint64_t lastPoint = 0; //The last position of the iterator
	for (int i = 0; i < 102400; i++)
	{
		auto it = contents.find(buffer[i]);
		//It's going to find it since it was created off it, so no need for a conditional if it!=end
		returnValue.insert(it->first - lastPoint); //The difference of the position of the iterator from the last position of the iterator (from 0 or the loop cycle)
	}
	return returnValue;
}