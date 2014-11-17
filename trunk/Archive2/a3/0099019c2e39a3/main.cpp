combine :: [a] -> [(a, a)]
combine (x1:x2:xs) = (x1,x2):combine xs
combine [] = []
            
main :: IO ()
main = do
    print $ combine ["Questions", "that", "may", "already", "have", "your", "correct", "answer"]