module Player (Player, getHealth, getScore, hit) where

data Player = 
    Player
        { getHealth     :: Int
        , getScore      :: Int }
    deriving (Eq)
    
hit :: Player -> Player
hit (Player health score) = Player (health - 1) (score - 10)

main :: IO ()
main = putStr "Ok"