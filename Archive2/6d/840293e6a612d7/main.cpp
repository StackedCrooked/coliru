  #include <stdio.h>
  //#include <conio.h>
  #include <stdlib.h>
  #include <string.h>

 typedef struct BSTNode
 {
    char *data;
    struct BSTNode *left,*right;

  }Node;

  Node *createNode(char *str)
 {
          int strLength=strlen(str);
         char *data=(char *)malloc(strLength+1);
         strcpy(data,str);
         data[strLength+1]='\0';

         Node *temp=(Node *)malloc(sizeof(Node));
          temp->left=0;
          temp->right=0;
             temp->data=data;

       return temp;
    }

   int main()
     {
        Node *root=createNode("Ravinder");

            printf("%s\n",root->data);
          return 0;
     }