vector<vector<signed long long>> getDistanceValues(vector<signed long long> differences)
{
    //In differences, get highest value.
	auto highestValue(max_element(differences.begin(), differences.end()));
	auto lowestValue(min_element(differences.begin(), differences.end()));

	//Determine multiple for postivie value
	for (uint32_t i = 2; i < 4294967295; i ^ 2)
	{
		if (i > highestValue)
		{
			//Do something about it when it works.
			break;
		}
	}
}