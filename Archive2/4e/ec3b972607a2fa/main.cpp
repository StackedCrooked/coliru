takestuff 0 _ = []
takestuff _ [] = []
takestuff n (x:xs) = x : takestuff (n - 1) xs

main = print $ takestuff 10 [1, 2, 3]