
takestuff 0 _ = []
takestuff x li
    | x > length li = li
    | otherwise = head li:takestuff (x-1) (tail li)

takestuff' 0 _ = []
takestuff' _ [] = []
takestuff' n (x:xs) = x : takestuff' (n - 1) xs

main :: IO ()
main = do
    print $ takestuff 10 [1, 2, 3]
    print $ takestuff' 10 [1, 2, 3]