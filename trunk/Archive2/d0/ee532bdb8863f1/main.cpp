

main () 
{ 
  int userNo [9] = {1, 2, 3, 4, 5, 6, 7, 8, 9}; 
  float ultarCloud [9] = {12.04, 17.33, 8.9, 2.1, 13.75, 23.2, 25.0, 19.0, 5.34}; 
  int scan; 
  int accountNo; 
  int found = 0; 
  int choice = 0; 
  for (scan=0; scan<10; scan++) 
  { 
    printf("\n\t\tPlease enter your Ultra-Cloud account No.:"); 
    scanf(" %d", &account); 
    if (accountNo == userNo[scan]) 
    { 
      found = 1; //statement becomes true 
      break; 
    } 
  } 
  if (found = 1) 
  { 
  
  }
}