unordered_set<signed long long> getValues(unordered_set<signed long long> contents, char buffer[102400])
{
    unordered_set<signed long long> returnValue; //+4, -32, +52, so on..
	signed long long lastPoint = 0; //The last position of the iterator
	for (int i = 0; i < 102400; i++)
	{ 
		auto it = contents.find(buffer[i]);
		//It's going to find it since it was created off it, so no need for a conditional if it!=end
		returnValue.insert(it - lastPoint); //The difference of the position of the iterator from the last position of the iterator (from 0 or the loop cycle)
	}
	return returnValue;
}