{-
Patricia B Ribeiro
For ECOM11A - Discreet Math Laboratory
Universidade Federal de Itajubá - IESTI
Itajubá - MG, 2022
-}
import System.Process

main = do
  let db = []
  menu db

type Database = [Disc]
type Disc = (String,String,Float,Int)

menu:: Database -> IO()
menu db = do
  putStrLn " 1- New Disc. \n 2- Delete disc by tittle.\n 3- Delete disc by artist.\n 4- Find disc by tittle.\n 5- Find disc by artist. \n 6- Find disc by year. \n 7- Show all discs. \n 8- End Program. \n"
  putStrLn "Insert your option: "
  opt <- readLn
  db <- carryout db opt
  if opt == 8 then return () else menu db

info :: IO Disc
info = do
  putStrLn "Album name:"
  album <- getLine --readLn is returning parse error when reading String, getLine works here.

  putStrLn "Artist name:"
  artist <- getLine

  putStrLn "Estimated price:"
  price <- readLn

  putStrLn "Release year:"
  year <- readLn

  return (album,artist,price,year)

carryout :: Database -> Int -> IO Database
carryout db opt = if opt == 1
  then do
    putStrLn "Inserting disc..."
    disc <- info
    return (insert db disc)
  else if opt == 2 then do
    putStrLn "Removing by album tittle..."
    putStrLn "Album name:"
    aux <- getLine
    return (removeTittle db aux)

  else if opt == 3 then do
    putStrLn "Removing by artist..."
    putStrLn "Artist name:"
    aux <- getLine
    return (removeArtist db aux)

  else if opt == 4 then do
    putStrLn "Album name:"
    aux <- getLine
    putStrLn "Searching by album tittle..."
    searchTittle db aux
    return db

  else if opt == 5 then do
    putStrLn "Artist name:"
    putStrLn "Searching by artist..."
    aux <- getLine
    searchArtist db aux
    return db

  else if opt == 6 then do
    putStrLn "Release Year:"
    num <- getLine
    putStrLn "Searching by release year..."
    searchYear db (read num :: Int)
    return db

  else if opt == 7 then do
    putStrLn "Showing All Discs: \n"
    printout db
    return db

   else do
     putStrLn "Ending program..."
     return db

insert :: Database -> Disc -> Database
insert [] dsk = [dsk]
insert ((ha,hb,hc,hd):t) (a,b,c,d) = if d <= hd then [dsk] ++ db  else [h] ++ insert t dsk
  where
    db = ((ha,hb,hc,hd):t)
    h = (ha,hb,hc,hd)
    dsk = (a,b,c,d)

removeTittle :: Database -> String -> Database
removeTittle [] _ = []
removeTittle ((a,b,c,d):t) str = if a == str then t else (a,b,c,d): removeTittle t str --functions fst and snd didn't work with the head, used (a,b,c,d) instead.

removeArtist :: Database -> String -> Database
removeArtist [] _ = []
removeArtist ((a,b,c,d):t) str = if b  == str then removeArtist t str else (a,b,c,d): removeArtist t str

searchTittle :: Database -> String -> IO ()
searchTittle [] _ = do putStrLn "\n"
searchTittle ((a,b,c,d):t) str = if a == str then do
   putStrLn ("Album: " ++ a)
   putStrLn ("Artist: " ++ b)
   putStrLn ("Price: $" ++ show(c))
   putStrLn ("Release Year: " ++ show(d))
   putStrLn ""
   searchTittle t str
  else searchTittle t str

searchArtist :: Database -> String -> IO ()
searchArtist [] _ = do putStrLn "\n"
searchArtist ((a,b,c,d):t) str = if b == str then do
   putStrLn ("Album: " ++ a)
   putStrLn ("Artist: " ++ b)
   putStrLn ("Price: $" ++ show(c))
   putStrLn ("Release Year: " ++ show(d))
   putStrLn ""
   searchArtist t str
  else searchArtist t str

searchYear:: Database -> Int -> IO ()
searchYear [] _ = do putStrLn "\n"
searchYear((a,b,c,d):t) int = if d == int then do
   putStrLn ("Album: " ++ a)
   putStrLn ("Artist: " ++ b)
   putStrLn ("Price: $" ++ show(c))
   putStrLn ("Release Year: " ++ show(d))
   putStrLn ""
   searchYear t int
  else searchYear t int

printout :: Database -> IO ()
printout [] = do putStrLn ""
printout ((album,artist,price,year):t) = do
  putStrLn ("Album: " ++ album)
  putStrLn ("Artist: " ++ artist)
  putStrLn ("Price: $" ++ show(price))
  putStrLn ("Release Year: " ++ show(year))
  putStrLn ""
  printout t
