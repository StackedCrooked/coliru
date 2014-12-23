module Main (main) where

import qualified Data.Array as Array
import qualified Foreign.Ptr as Ptr

foo :: Ptr.Ptr a -> Int
foo _ = 0

main :: IO ()
main = print $ foo $ Array.listArray (0, 2) [1, 2, 3]
