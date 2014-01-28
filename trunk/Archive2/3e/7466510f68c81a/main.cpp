import Control.Monad
import Data.Array
import System.Exit
import System.IO
 
main = do
    let a = listArray (0,10) $ repeat 0
    loop a
    where
    	loop a = do
			iseof <- isEOF
			when iseof $ do
				print a
				exitSuccess
			l <- hGetLine stdin
			let i = (read l)
			let v = a ! i
			loop $ a // [(i, v+1234)]