main :: IO ()
main = do
    print $ [(a, b) | (a:tail) <- tails xs, b <- tail]