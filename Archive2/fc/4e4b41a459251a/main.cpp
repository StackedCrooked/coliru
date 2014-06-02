{-# LANGUAGE FlexibleInstances #-}
{-# LANGUAGE OverlappingInstances #-}
{-# LANGUAGE UndecidableInstances #-}

import Data.Map (Map)
import Data.List (intersperse)
import qualified Data.Map as Map

class Renderable a where
    render :: a -> String

instance Renderable Char where
    render c = [c]

instance (Renderable a) => Renderable [a] where
    render l = concat . intersperse " " . map render $ l

instance (Renderable k, Renderable v) => Renderable (Map k v) where
    render m = 
        let fn k v s = concat [s, render k, ": ", render v, "\n"]
        in Map.foldrWithKey fn "" m

instance (Show a) => Renderable a where
    render = show
    
main = putStr . render $ 
    Map.fromList
        [ ('a', [1, 2, 3] :: [Int])
        , ('b', [3, 4, 5]) ]