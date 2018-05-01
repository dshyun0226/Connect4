# Connect4
Connect4 solving algorithm with Heuristic and Rule based


Rule Based:
1. If I can win the game by putting a piece on column X, put it.
2. Else If I lose when the opposite player puts a piece on column X after my turn, put it.
3. Else, Get the X that has the maximum score value.
   Assume that I put a piece in column X, the score value of X is derived by below. (To get higher score)
    1) score += the number of line that can be made 4 connected. The line must include the last piece.
    2) score + the number of longest connected pieces include the last one.
   In additional, assume that the opposite player put a piece above my last piece immediately. (To consider the next situation)
    1) If I lose, in that case, never put my last piece in X.
    2) score -=  the number of line that can be made 4 connected. The line must include the opposite player's last piece.
    3) score - the number of longest connected pieces include the opposite player's last piece.
    
   Assume that opposite player put a piece in columns X. (To prevent that the opposite player get higher score)
    1) score += the number of line that can be made 4 connected. The line must include the last piece.
    2) score + the number of longest connected pieces include the last one.
    

Well known Counter Examples

1) 3, 2, 4, 5 - by opposite player
