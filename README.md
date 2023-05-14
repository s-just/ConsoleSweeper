# ConsoleSweeper

A simple program that builds a tilemap for minesweeper and lets the user play through the console.

The project is not finished as I need to still fix the neighbour counts displaying properly when playing in the console.

----

Fixed a bug where my map bounds logic was not counting neighbors that were on the edge of the map. 

if (i - 1 >= 0 && j - 1 >= 0 && i + 1 < ROWS && j + 1 < COLS)

To fix this instead of making the conditional logic over-complicated, I created a small function for determining if a position is within the bounds of the 2d vector map.

Since C++ vectors do not check for out of bounds or return null, I use an explicit check once before accessing the tile, and again for each tile that would be it's neighbor.

I would like to return whether or not the game is over when revealing a tile so next time I work on this I will add a struct or class to define the game state.

---

I added a struct for the game state and there are no current issues apart from not dealing with bad user input.
