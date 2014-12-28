fact 0 = 1
fact n = n * fact (n - 1)

main = do print $ fact 1000