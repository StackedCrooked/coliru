#define USER_EVENT_ENTER       1
#define USER_EVENT_LEAVE       2
#define USER_EVENT_OVERLOAD    3

typedef struct ICMCONTAINERDATA_STRUCT
{
  char  szContainerName[33];
  char  szContainerVal[255];
}ICMCONTAINERDATA_STRUCT;

typedef void * (*PFMALLOC ) (size_t n);

typedef struct _ICMUSERSTRUCT
{
    int    lUserEvent;
    char   szWPCompID[19];
    char   szWPItemID[27];
    short  sWPVersionID;
    char   szRouteSel[33];
    short  sUpdateFlag;
    short  sNumContainerData;
    const ICMCONTAINERDATA_STRUCT *pContainerDataStructIn;
    ICMCONTAINERDATA_STRUCT *pContainerDataStructOut;
    PFMALLOC mallocf;
}  ICMUSERSTRUCT;

#include <stdio.h>



extern long WXV2TBAUE (ICMUSERSTRUCT *pCMStruct) 
{
    char envStr[256];
    ICMCONTAINERDATA_STRUCT * pContainerDataStruct;

    pContainerDataStruct = (ICMCONTAINERDATA_STRUCT *) malloc (sizeof(ICMCONTAINERDATA_STRUCT) * pCMStruct->sNumContainerData);

    printf(pCMStruct->szWPItemID);

    if (pContainerDataStruct != 0) free(pContainerDataStruct);
    
    return 0;
}