#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>
#include <atomic>
#include <semaphore.h>


class Validator
{
public:
enum ValidationError
{
    NO_MULTIPLE_3,
    NI_MULTIPLE_4
}

    Validator();
    
    setData(Data data);
    bool isValid();
    enum ValidationError getCause() cost;
}


int main()
{
Data data;

Validator validator;
validator.setData(data);
if (!validator.isValid())
    return validator.getCause();
    
    return 0;
}
