
Excerpt from LYAH:
But what if we wanted a function that says the numbers from 1 to 5 and says 
"Not between 1 and 5" for any other number? Without pattern matching, 
we'd have to make a pretty convoluted if then else tree.
 
sayMe :: (Integral a) => a -> String  
sayMe 1 = "One!"  
sayMe 2 = "Two!"  
sayMe 3 = "Three!"  
sayMe 4 = "Four!"  
sayMe 5 = "Five!"  
sayMe x = "Not between 1 and 5"  
 
Pretty convoluted you say?
std::string sayMe(int num)
{
    switch(num)
    {
    case 1: return "One";
    case 2: return "Two";
    case 3: return "Three";
    case 4: return "Four";
    case 5: return "Five";
    default: return "Not between one and five";
    }
}