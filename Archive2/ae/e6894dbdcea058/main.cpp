module Main where

import Prelude hiding (id)
import Data.List (intersperse)
import System.Random
import Control.Applicative
 
type PieceId        = String
type PieceContent   = Char
 
data Piece = Piece { character  :: PieceContent
                   , id         :: PieceId
                   , northId    :: PieceId
                   , eastId     :: PieceId
                   , southId    :: PieceId
                   , westId     :: PieceId
                   } deriving (Eq)
                   
instance Show Piece where
    show (Piece c i ni ei si wi) = concat . intersperse "\t" $ [i, [c], ni, ei, si, wi]
 
noneId :: String
noneId = "VUOTO"
 
type UnsolvedPuzzle = [Piece]
type SolvedPuzzle  	= [[Piece]]
		  
calcNorthId :: (Int, Int) -> Int -> PieceId
calcNorthId (w, _) i =
	let x = i - w
	in if x >= 0
		then show x
		else noneId
	
calcEastId :: (Int, Int) -> Int -> PieceId
calcEastId (w, _) i =
	let x = i + 1
	in if (x `mod` w) /= 0
		then show x
		else noneId
		
calcSouthId :: (Int, Int) -> Int -> PieceId
calcSouthId (w, h) i =
	let x = i + w
	in if (x `div` w) < h
		then show x
		else noneId
		
calcWestId :: (Int, Int) -> Int -> PieceId
calcWestId (w, _) i =
	let x = i - 1
	in if (i `mod` w) /= 0
		then show x
		else noneId

generatePieces :: (Int, Int) -> Int -> String -> [Piece]
generatePieces _ _ [] = []
generatePieces sz i (c:cs) = 
	(Piece c (show i) (calcNorthId sz i)
			  	 	 (calcEastId sz i)
			  		 (calcSouthId sz i)
			  		 (calcWestId sz i)) : generatePieces sz (i + 1) cs
 
generateSolvedPuzzle :: (Int, Int) -> String -> [Piece]
generateSolvedPuzzle (w, h) s
	| w * h /= length s = error "String length is dependent on the puzzle's size"
	| otherwise			= generatePieces (w, h) 0 $ s

shuffle :: [a] -> IO [a]
shuffle [] = return []
shuffle lst = do
    (e, rest) <- pickElem <$> getIx
    (e:) <$> shuffle rest
    where
    getIx = getStdRandom $ randomR (1, length lst)
    pickElem n = case splitAt n lst of
        ([], s) -> error $ "failed at index " ++ show n
        (r, s)  -> (last r, init r ++ s)

main :: IO ()
main =
	let p = generateSolvedPuzzle (4, 3) "ABCDEFGHILMN"
	(shuffle p) >>= (mapM_ print)