struct DescriptorByte
{
    unsigned char IsImmedCalc : 1;
    unsigned char IsPrefix : 1;
    unsigned char NoMemOp : 1;
    unsigned char Size : 5;
};

struct OpcodeList
{
    
    
    
    DescriptorByte ADD_EB_GB;
    DescriptorByte ADD_EV_GV;
    DescriptorByte ADD_GB_EB;
    DescriptorByte ADD_GV_EV;
    DescriptorByte ADD_8_OI =   { TRUE, FALSE, TRUE, OPBASE + IMMED_8 };
    DescriptorByte ADD_32_OI =  { TRUE, FALSE, TRUE, OPBASE + IMMED_32 };
    DescriptorByte PUSH_ES =    { TRUE, FALSE, TRUE, OPBASE };
    DescriptorByte POP_ES =     { TRUE, FALSE, TRUE, OPBASE };
    DescriptorByte OR_EB_GB;
    
        //ETC
        
        
    DescriptorByte array[] = {
      ADD_EB_GB,   ADD_EV_GV, ADD_GB_EB, ADD_GV_EV, ADD_8_OI, ADD_32_OI,PUSH_ES,POP_ES,OR_EB_GB
      };
};