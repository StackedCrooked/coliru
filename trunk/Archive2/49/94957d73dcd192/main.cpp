
g :: [Double] -> Double
g = sum . takeWhile (< 10000) . map (^2)

main :: IO ()
main = putStr . show $ g [1, 2, 3, 4, 5]