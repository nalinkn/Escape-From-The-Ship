# Escape-From-The-Ship
This is a game that takes in a map of a spaceship as input and returns a path to the hanger for the player to escape with.
The user has two options for how the escape route will be found. Both methods utilize a backtracking algorithm, however one uses a stack-based approach (LIFO) while the other uses a queue-based approach (FIFO).
The user also ahs two options for the input. It can either be a map (as mentioned before) or a list of coordinates with symbols indicating special objects (everything other than floor tiles) at each coordinate.
I included a few sample maps to show what the input should look like.
Symbols: 
Start - S, Hanger - H, Wall - #, Floor Tile - ., Elevator - E

