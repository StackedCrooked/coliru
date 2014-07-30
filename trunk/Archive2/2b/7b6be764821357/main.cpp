To find the problems in your code, lets try debugging it!  First, we'll tell it to give us more information, listing the numbers it thinks are divisors:

        cout << num << "'s divisors are:\t";
        for(j=1;j<=i;j++)
        {
            if (num%j == 0)
            {
                cout << j << ' ';
                ++div;
            }
        }
        cout << '\n';

Now when we run it, it tells us what's going on:

    1's divisors are:    1 
    3's divisors are:	1 
    6's divisors are:	1 2 3 
    10's divisors are:	1 2 
    15's divisors are:	1 3 5 
    21's divisors are:	1 3 
    28's divisors are:	1 2 4 7 
    36's divisors are:	1 2 3 4 6 
    45's divisors are:	1 3 5 9 
    55's divisors are:	1 5 

Notice something odd?  All of the numbers are missing themselves, and many are missing large divisors, like 21 should have 7.  So we doublecheck the code:

    for(j=1;j<=i;j++)

Yup.  There's the bug, you only count to `i`.  When checking `21`, `i` is only `6`, so you're not finding the `7` nor the `21` divisors.  The simple fix is to iterate all the way to `num`.

An additional thing to notice is that the number of divisors doesn't climb evenly.  What if there is a number with 501 divisors, but there isn't any with 500 divisors?  In that case 


    for(i=1;div != 500;)
    { 
        //....
        if(div == 500)
        {
            cout << num;
            exit(0);
        }

Your code is an infinite loop.  If `div` never hits 500 _exactly_, then your code just calculates forever.  I don't think this is causing your problem, but it _is_ a bug.