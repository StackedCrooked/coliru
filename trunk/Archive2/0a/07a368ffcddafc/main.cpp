import Data.Foldable hiding (toList, concat)
import Control.Applicative
import Data.List (intersperse)
import Prelude hiding (foldr)
import qualified Prelude as P

data Mat a
    = Mat
        { size :: (Int, Int)
        , toList :: [a] }
    deriving (Eq)

mat :: (Int, Int) -> [a] -> Mat a
mat (r, c) l
    | length l == r * c = Mat (r, c) l
    | otherwise = 
        error . concat $
            [ "Trying to initialize a matrix of size "
            , show r, "x", show c, " with "
            , show (length l), " elements." ]


mat2x2  = mat (2, 2)
mat3x3  = mat (3, 3)
mat4x4  = mat (4, 4)

vec2 vx vy          = mat (2, 1) [vx, vy]
vec3 vx vy vz       = mat (3, 1) [vx, vy, vz]
vec4 vx vy vz vw    = mat (4, 1) [vx, vy, vz, vw]

rows :: Mat a -> Int
rows = fst . size

cols :: Mat a -> Int
cols = snd . size

elems :: Mat a -> Int
elems m = cols m * rows m

showRow :: (Show a) => [a] -> String
showRow = (++ "\n") . concat . intersperse " " . map show

showMat :: (Show a) => Int -> [a] -> String
showMat n [] = ""
showMat n ls =
    let (x, r) = splitAt n ls
    in  showRow x ++ showMat n r

instance (Show a) => Show (Mat a) where
    show m = showMat (cols m) (toList m)

transpose :: Mat a -> Mat a
transpose m =
    let c = cols m
        r = rows m
    in  Mat (c, r) $ 
        map (flip get $ m) [(b, a) | a <- [0..c-1], b <- [0..r-1]]

isSquare :: Mat a -> Bool
isSquare m
    | rows m == cols m  = True
    | otherwise         = False


get :: (Int, Int) -> Mat a -> a
get (r, c) m
    | (rows m > r) && cols m > c = (toList m) !! (r * (cols m) + c)
    | otherwise = undefined

x = get (0, 0)
y = get (0, 1)
z = get (0, 2)
w = get (0, 3)

instance Functor Mat where
    fmap f m = Mat (size m) (fmap f (toList m))

instance Foldable Mat where
    foldr f c = foldr f c . toList

instance (Num a) => Num (Mat a) where
    a + b
        | size a == size b = Mat (size a) (zipWith (+) (toList a) (toList b))
        | otherwise = undefined
    a * b
        | size a == size b = Mat (size a) (zipWith (-) (toList a) (toList b))
        | otherwise = undefined
    abs = fmap abs
    signum = fmap signum
    fromInteger a = Mat (1, 1) [fromInteger a]
    negate = fmap negate
    
main = do
    print (transpose $ vec3 0 1 2)