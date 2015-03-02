//Error:
//In file included from C:\Project\CGame.h:9:0,
//                 from C:\Project\CEnemy.h:3,
//                 from C:\Project\CEnemy.cpp:1:
//C:\Project\CEnemyHealth.h:11:16: error: field 'cenemy1' has incomplete type

//CEnemyHealth.h
#ifndef CENEMYHEALTH_H
#define CENEMYHEALTH_H
//#include "CEnemy.h"

class CEnemy;

class CEnemyHealth
{
    public:
        CEnemyHealth();
        virtual ~CEnemyHealth();
        void Set(CEnemy &passed_cenemy); 
        CEnemy cenemy1;                  //error: "field 'cenemy1' has incomplete type"
    protected:
    private:
};

#endif // CENEMYHEALTH_H
