{-# LANGUAGE DeriveFunctor, PatternGuards #-}

module Main where

import Control.Applicative
import Control.Monad

import Data.List (unfoldr)

import Text.Printf (printf)

-- For want of Control.Comonad
class Functor w => Comonad w where
    extract :: w a -> a
    duplicate :: w a -> w (w a)
    extend :: (w a -> b) -> w a -> w b
    extend f = fmap f . duplicate

-- For want of whichever list zipper module

-- Forbid zippers over empty lists for convenience
data Zipper a = Zipper [a] a [a]
    deriving (Show, Read, Eq, Ord, Functor)

fromList :: [a] -> Zipper a
fromList (a:as) = Zipper [] a as
fromList _ = error "zipper over an empty list"

toList :: Zipper a -> [a]
toList (Zipper pre focus post) = focus:reverse pre ++ post
    
prefix :: Zipper a -> [a]
prefix (Zipper pre _focus _post) = reverse pre

postfix :: Zipper a -> [a]
postfix (Zipper _pre _focus post) = post

left :: Zipper a -> Maybe (Zipper a)
left (Zipper (before:pre) focus post) = Just $ Zipper pre before (focus:post)
left _ = Nothing

right :: Zipper a -> Maybe (Zipper a)
right (Zipper pre focus (top:post)) = Just $ Zipper (focus:pre) top post
right _ = Nothing

instance Comonad Zipper where
    extract (Zipper _pre focus _post) = focus
    duplicate z = Zipper lefts z rights
        where
            lefts = unfoldr ((dup <$>) . left) z
            rights = unfoldr ((dup <$>) . right) z
            dup = join (,)

-- Business starts here
data Item = Character Char | Dashes Int
    deriving (Show, Read, Eq, Ord)
    
parse :: String -> [Item]
parse [] = []
parse l@('-':_cs) = Dashes (length dashes):parse rest
    where
        (dashes, rest) = span (== '-') l
parse (c:cs) = Character c:parse cs

unparse :: [Item] -> String
unparse [] = []
unparse (Character c:is) = c:unparse is
unparse (Dashes d:is) = replicate d '-' ++ unparse is

splitOnDashes :: [Item] -> [Zipper Item]
splitOnDashes [] = []
splitOnDashes items = do
    let universe = toList . duplicate $ fromList items
    candidate <- universe
    guard $ focusOnDashes candidate
    return candidate
        where
            focusOnDashes z | Dashes _ <- extract z = True
            focusOnDashes _ = False

insertions :: a -> [a] -> [[a]]
insertions a [] = [[a]]
insertions a (x:xs) = (a:x:xs):map (x:) (insertions a xs)

mixItUp :: [Item] -> [[Item]]
mixItUp items = do
    split <- splits
    insertions (extract split) (prefix split ++ postfix split)
        where
            splits = splitOnDashes items
    
main = do
    let example = "A-B--C---D"
    printf "Original: %s\nResults:\n" example 
    forM_ (mixItUp . parse $ example) (print . unparse)