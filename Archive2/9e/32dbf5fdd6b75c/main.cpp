every :: Int -> [a] -> [a]
every nth [] = []
every nth (x:xs) = x : every nth (drop (nth - 1) xs)

diffs :: (Ord a) => [a] -> Bool
diffs as = and $ zipWith (<) (stride as) (stride $ drop1 as)
    where
        stride = every 2
        drop1 = drop 1

main = do
    print $ diffs [0..9]
    print $ diffs ([]::[Int])