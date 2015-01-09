char * readTheFile()
{
    static char mypagefile[17179869184];
	ifstream myfile;
	myfile.open("my16gigfile", ios::in | ios::out | ios::binary);
	myfile.read(mypagefile, 17179869184);
	myfile.close();

	return mypagefile;
}
