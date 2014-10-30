main :: IO ()
main = do
    let xs = [1, 2, 3, 4]
    print $ [(a, b) | (a:tail) <- tails xs, b <- tail]