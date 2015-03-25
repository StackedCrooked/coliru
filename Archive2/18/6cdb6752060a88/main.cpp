#!/usr/bin/env runhaskell

{-# LANGUAGE TupleSections #-}

import Control.Applicative
import Control.Monad

import Data.Map (Map)
import qualified Data.Map as Map

import System.IO
import System.Environment

analyse pred path = withFile path ReadMode $ \h -> do
    cs <- hGetContents h
    return . Map.fromListWith (+) . map (,1::Int) . filter pred $ cs

counts pred args = foldM (\m p -> Map.unionWith (+) m <$> analyse pred p) Map.empty args

main = do
    (set:args) <- getArgs
    result <- counts (`elem` set) args
    print result