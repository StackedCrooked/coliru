-- Srm632Div2Lev2 PotentialGeometricSequence
-- http://community.topcoder.com/stat?c=problem_statement&pm=13390

module Srm632Div2Lev2 where

---------------------------------------------------------
handler [_]      = True
handler [_,_]    = True
handler (x:y:xs) =                                      -- [7,6,5]
            all (\diff -> diff == y - x) $              -- True
            map (\(prev, cur) -> cur - prev) $          -- [-1,-1]
            zip (x:y:xs) (y:xs) -- [(prev, cur)]        -- [(7,6), (6,5)]

---------------------------------------------------------
numberOfSubsequences xs =                               -- [8,7,6,5]
            sum $                                       -- 10
            map (\b->if b then 1 else 0) $              -- [1,     1     .. 1    ]
            map handler $                               -- [True,  True  .. True ]
            map (\(f,s)-> take (s-f+1) (drop f xs)) $   -- [[8],   [8,7] .. (5,5)] 
            [(x,y) | x<-[0..max], y<-[0..max], x <= y]  -- [(0,0), (0,1) .. (3,3)]
            where max = (length xs) - 1

-- | The main entry point.
main :: IO ()
main = do
    print $ numberOfSubsequences [0,1,2]
    print $ numberOfSubsequences [1,2,4]
    print $ numberOfSubsequences [3,2,1,0]
    print $ numberOfSubsequences [1,2,4,8,16]
    print $ numberOfSubsequences [1,3,5,5,5,5,64,4,23,2,3,4,5,4,3]

{-| Output
6
5
10
9
37
-}