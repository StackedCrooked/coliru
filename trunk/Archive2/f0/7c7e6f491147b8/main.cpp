//CEnemyHealth.h file
#ifndef CENEMYHEALTH_H
#define CENEMYHEALTH_H

#ifndef CENEMY_H
#define CENEMY_H
#include <iostream>

class CEnemy
{
    public:
        CEnemy();
        virtual ~CEnemy();
    protected:
    private:
};

#endif // CENEMY_H

class CEnemyHealth
{
    public:
        CEnemyHealth();
        virtual ~CEnemyHealth();
        void Set(CEnemy &passed_cenemy); //error: "C:\Project\CEnemyHealth.h|10|error: 'CEnemy' has not been declared|"
        CEnemy cenemy1;                  //error: "C:\Project\CEnemyHealth.h|11|error: 'CEnemy' does not name a type|"
    protected:
    private:
};

#endif // CENEMYHEALTH_H

//CEnemy.h Separate File
