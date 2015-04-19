algo :: [a] -> [a]
algo [] = []
algo (h:t) = reverse $ h:algo t

main = do
    -- that doesn't quite look like what we want
    print . algo $ [0..35]
    
    -- good enuff!
    -- ignore last element
    print . algo $ 0:[0..35]