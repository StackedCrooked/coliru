groupEvery :: Int -> [a] -> [[a]]
groupEvery n lst
    | length lst < n = []
    | otherwise      = take n lst : groupEvery n (tail lst)

ngrams :: Int -> String -> [String]
ngrams n = concatMap (groupEvery n . fillWord '_') . words
    where fillWord f w = f : (w ++ replicate (n - 1) f)

main :: IO ()
main = print $ ngrams 3 "This is simple and a example"