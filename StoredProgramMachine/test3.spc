SET      @0 50        #D0 = 50
SET      @1 100       #Set D1 = 100
SET      @2 5         #Set D2 = 2, this is our data memory cell to write to index
SET      @3 1         #Set quantity to increment by
BRANCHEQ @0 @1 10     #If D0 == D1, jump to 5
SETA     @2 0
ADD      @2 @3 @2     #Increment D2 memory cell counter
ADD      @0 @3 @0     #Increment D0 count by 1
JUMP      5
END
