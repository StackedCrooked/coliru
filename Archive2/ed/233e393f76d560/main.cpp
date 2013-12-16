genIxs sizes = do (x, s) <- zip [0..] $ map (enumFromTo 0.subtract 1) sizes
                  y <- s
                  return (x, y)

main = do
    print $ genIxs [1,2,3]