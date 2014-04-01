#include <iostream>
#include <string>
#include <vector>



int main()
{
    
     
   /*
       CPersistData data(TL_CLASS_SERVICELIST_MGR, 1, pRawServiceList, length);
       E_LM_Result_Set result = lm.Set(data);
    */
    
    // original data
    std::vector<int32_t> originalVector {1, 2, 3, 4};

       
    // store it to persistency
    uint8_t* persistentData = reinterpret_cast<uint8_t*>(originalVector.data());
 
 
    /* 
       //Persistenz interface liefert  uint8_t array und Länge: 
       uint8_tCLastMode lm(ELM_OEM_SERVICELIST);
       uint32_t nLen = 0;
       E_LM_Result_Get res = lm.GetLength(TL_CLASS_SERVICELIST_MGR, 1, nLen);
       
       uint8_t* pDataBuffer = NULL;
       ACE_NEW_NORETURN(pDataBuffer, uint8_t[nLen]);

       E_LM_Result_Get result = lm.GetData(TL_CLASS_SERVICELIST_MGR, 1, pDataBuffer, nLen);
    */
  
    // falsch lesen    
    size_t size = 16; 
    std::vector<int32_t> targetVector;
    targetVector.assign( persistentData, persistentData+size );
  /*
    for( unsigned i=0; i<size; i++)
        std::cout << i << '\t' << targetVector[i] << std::endl;
 */ 
 
  
     // Beispiel richtig lesen    
      targetVector.assign( reinterpret_cast<int32_t*>(persistentData),  reinterpret_cast<int32_t*>(persistentData + size));
   
      for( unsigned i=0; i<targetVector.size(); i++)
         std::cout << i << ':' << targetVector[i] << std::endl;
 
 
 
 

 
}
