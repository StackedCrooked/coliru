int compare(char buffer[102400])
{
    if (!everRun)
	{
		bytes.insert(uint64_t(buffer[0]));
		//If it's never run, read the first byte into the vector.
	}
	for (int i = 0; i < 102400; i++)
	{
		auto search = bytes.find(uint64_t(buffer[i]));
		if (search != bytes.end())
		{
			//Found. Don't add the new byte.
		}
		else
		{
			bytes.insert(uint64_t(buffer[i]));
			//Not found. New byte. insert it into the map.
			cout << "New byte: " << uint64_t(buffer[i]) << "\n";
		}
	}
	cout << "The size of a random value in buffer before is " << uint64_t(buffer[5253]) << "\n"; //Proof that it's reading the same values.
	cout << "The size of the vector is " << bytes.size(); 
	return 0;
}