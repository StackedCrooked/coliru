x :: IO ()
x = putStrLn "x"

y :: IO ()
y = putStrLn "y"

z :: IO ()
z = putStrLn "z"

main = x >> y >> z