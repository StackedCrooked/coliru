{-# LANGUAGE TypeFamilies, FlexibleInstances #-}

module Main where

-- Silly API
class Referenceable a where
    type ReferenceType a :: *
    expand :: ReferenceType a -> IO a

-- Post & posts example
type PostID = Int
type Limit  = Int

data Post =
    Post { postId    :: PostID
         , postTitle :: String
         , postBody  :: String }
    deriving (Eq)
    
data PostHref = PostHref PostID
data PostListHref = PostListHref Limit
    
instance Referenceable Post where
    type ReferenceType Post = PostHref
    expand (PostHref id) = do
        putStrLn $ "Fetching post with id = " ++ show id
        return $ Post id "Title" "Some body"
        
instance Referenceable [Post] where
    type ReferenceType [Post] = PostListHref
    expand (PostListHref lim) = do
        putStrLn $ "Fetching posts, given a limit of " ++ show lim
        return []

-- Usage
main :: IO ()
main = do
    _ <- expand (PostHref 1) :: IO Post
    _ <- expand (PostListHref 10) :: IO [Post]
    return ()