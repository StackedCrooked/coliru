import Data.HashMap.Strict (HashMap, fromListWith)

type A = String
type B = Int

list :: [(A, B)]
list = [("foo", 1), ("foo", 2), ("qux", 4)]

foo :: [(A, B)] -> HashMap A [B]
foo = fromListWith (:)
            
main :: IO ()
main = do
    print $ foo list