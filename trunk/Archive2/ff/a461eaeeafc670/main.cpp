fib 1 = 1
fib 2 = 1
fib n = fib (n-1) + fib (n-2)

weirdFib n k 
    | n <= k = fib n
    | True   = sum $ map (flip weirdFib k) [(n-k)..(n-2)]