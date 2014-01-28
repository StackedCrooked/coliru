#include <stdio.h>
#include <string>

using namespace std;
typedef uint Token;

const Token tokenBase=0x80000000;

enum        classId{
    classNoId=tokenBase,
    classPrimitiveId,
};

struct classInfo{classId id;wstring name;};

classInfo classInfos[]={ 
    {classNoId,L"classNoID"},
    {classPrimitiveId,L"classPrimitiveId"},
};

int main(){
    int id=classInfos[0].id;
    return 0*id;
}