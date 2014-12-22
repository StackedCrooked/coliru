class IsVec2 vec where
    toPair   :: vec a -> (a, a)
    fromPair :: (a, a) -> vec a
    
data Vec2 a = Vec2 a a deriving (Eq, Show)

instance IsVec2 Vec2 where
    toPair (Vec2 a b) = (a, b)
    fromPair (a, b)   = (Vec2 a b)
    
doSomething :: IsVec2 vec => vec Int -> vec Int
doSomething v =
    let (a, b) = toPair v
    in  fromPair (a + 1, b + 1)

main :: IO ()
main = print . doSomething $ (Vec2 10 50)