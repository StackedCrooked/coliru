import Data.Time (getCurrentTime, formatTime, diffUTCTime, UTCTime)
import System.Locale (defaultTimeLocale)

secondsFromEpoch :: UTCTime -> Int
secondsFromEpoch utc =
    let seconds = formatTime defaultTimeLocale "%s" utc
    in  read seconds

main :: IO ()
main = do
    currentTime <- getCurrentTime
    print $ secondsFromEpoch currentTime