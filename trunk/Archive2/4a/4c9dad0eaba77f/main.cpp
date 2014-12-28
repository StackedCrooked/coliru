char * buffer(string path, int position)
{
    static char buffer[102400];

    ifstream myfile;
	myfile.open(path, ios::in | ios::out | ios::binary);
	myfile.seekg(102400 * position, ios::beg); //Depending on the position (for later when it has to read another chunk of the file (in 100MB)
	myfile.read(buffer, 102400); //Read the first 100MB into buffer)
	myfile.close();

	return buffer; 
}