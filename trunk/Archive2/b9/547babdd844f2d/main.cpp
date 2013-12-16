genXs sizes = concat $ zipWith ($) (map replicate sizes) [0..]
genIxs sizes = zip (genXs sizes) $ concatMap (\x -> [0..x-1]) sizes

genIxs' _ _ [] = []
genIxs' accX accY (0:ss) = genIxs' (accX + 1) 0 ss
genIxs' accX accY (n:ss) = (accX, accY) : genIxs' accX (accY + 1) ((n - 1):ss)

main = do
    print $ genIxs [1,2,3]
    print $ genIxs' 0 0 [1,2,3]