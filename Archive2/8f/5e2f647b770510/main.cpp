char * buffer(string path, int position)
{
    static char buffer[102400];

	ifstream myfile;
	myfile.open(path, ios::in | ios::out | ios::binary);
	myfile.seekg(102400 * position, ios::beg); 
	myfile.read(buffer, 102400);
	myfile.close();

	return buffer;
}
