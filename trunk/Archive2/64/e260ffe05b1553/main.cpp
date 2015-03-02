#ifndef CENEMYHEALTH_H
#define CENEMYHEALTH_H
#include "CEnemy.h" //note this file does exist with my setup. It's a simple class skeleton nothing added. Just a normal blank one

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
