#include <stdio.h>
#include <string>

using namespace std;

int main()
{
  static const char* val1 = "hello";
    
	const char* val2 = "hello";
	
	const string val3 = "hello";
	
	printf("\nbefore: %s, %s, %s", val1, val2, val3.c_str());
	
	char* modifyingVal2 = const_cast<char*>(val2);
	//modifyingVal2 = "test";
	//strcpy(modifyingVal2, "fuck");
	
	printf("\nafter: %s, %s, %s, %s", val1,  val2, val3.c_str(), modifyingVal2);
	
	const char* stringChar = val3.c_str();
	printf("\nafter: %p, %p, %p, %p", (void*)val1, (void*)val2, (void*)stringChar, (void*)modifyingVal2);
	//printf("\nafter: %p, %p, %p, %p", (void*)&val1, (void*)&val2, (void*)stringChar, (void*)modifyingVal2);
	
	return 0;
}