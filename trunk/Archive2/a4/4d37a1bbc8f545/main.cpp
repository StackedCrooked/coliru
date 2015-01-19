#include<stdio.h>
#include<stdlib.h>

void build_intListUniqueNumRepeated (struct intList*ptr, struct intListUniqueNumRepeated*ptrptr)
{ init(ptrptr);
  while(ptr!=NULL)
  { add(ptrptr, ptr->value);
  }
}

void add(struct intListUniqueNumRepeated*ptrptr,int value)
{ while(*ptrptr!=NULL && (*ptrptr)->value<value);
  { ptrptr= &(*ptrptr)->next-ptr;
  }
  if (*ptrptr!=NULL && (*ptrptr)->value==value)
    (*ptrptr)->n_instances++;
  else
   pre_insert(ptrptr,value,1);
}

void pre_insert(struct intListUniqueNumRepeated**ptrptr, int value, int n_instances)
{struct intListUniqueNumRepeated*tmp_ptr;
tmp_ptr=(struct intListUniqueNumRepeated*)malloc(sizeof(struct intListUniqueNumRepeated));
(*ptrptr)->value=value;
(*ptrptr)->n_instances=n_instances;
(*ptrptr)->next-ptr=tmp_ptr;
}

  
