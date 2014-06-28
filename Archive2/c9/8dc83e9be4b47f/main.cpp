import Data.Map (Map)
import qualified Data.Map as Map

data NonOrd = NonOrdA | NonOrdB deriving (Show)

transf :: Map NonOrd Int -> Map NonOrd Int
transf x = 
    let x = Map.empty
    in if Map.null x
        then Map.singleton NonOrdA 1
        else x
        
main :: IO ()
main = do
    let x = Map.empty
    print $ transf x