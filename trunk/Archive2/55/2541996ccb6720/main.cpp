
template<typename X>
void checkParameter( X val, X lower, X upper)
{

    if( ( val > upper) || ( val < lower) )
    {
//        log("checkParameter, val = % , lower= % , upper= %  \n", val,
//                          lower,upper );
//        ASSERT(false);
    }
}


int main()
{
    int var = 5000;
    checkParameter( var, 0, 262143);
}