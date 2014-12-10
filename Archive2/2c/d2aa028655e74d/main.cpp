-- Srm632Div2Lev1 RunningAroundPark
-- http://community.topcoder.com/stat?c=problem_statement&pm=13391

module Srm632Div2Lev1 where

------------------------------------------------------
handler (prev, current) = if prev >= current then 1 else 0

------------------------------------------------------
numberOfLab n [] = 0
numberOfLap n xs = (sum $ 
                    map handler $
                    zip xs (tail xs) -- [(prev, cur)]
                    ) + 1

------------------------------------------------------
-- | The main entry point.
main :: IO ()
main = do
        print $ numberOfLap 3  [1,2,3]
        print $ numberOfLap 24 [6,6]
        print $ numberOfLap 3  [3,2,1]
        print $ numberOfLap 50 [1,3,5,7,9,2,4,6,8,10]

{-| Output
1
2
3
2
-}