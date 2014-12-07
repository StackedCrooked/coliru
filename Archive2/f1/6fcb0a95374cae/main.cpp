int main() 
{
  int arr[5][5];

   for (auto& row : arr) 
       for (auto& val : row)
            val = 1;  
}