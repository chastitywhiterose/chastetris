# chastetris
An very chaste(pure) version of Tetris using the Raylib library and C programming language.

Because I love playing Tetris, I used all my programming skills to make a simple game that I can play with a few features that I wish other Tetris games had.
There is infinite time to place the blocks because there is no gravity.
Additionally, you can press the '.' key to save the game at any time and then press ',' to reload to the previously saved state.
This means my game is the only Tetris game that lets you go back in time to fix mistakes!

Chaste Tris is my first complete video game I have made. It is obviously based on similar other games but easier because there is no gravity. Blocks can be freely moved up, down, left, and right with the arrow keys. They can be rotated with X or Y keys and can also be held for later use with C.

But my game also allows for a new feature that none of the other games have. It is possible to save the state of the game by pressing the . key and reload it with the , key to go back and correct mistakes. This makes it the perfect tool to test out playing styles which would be perfectly valid on other puzzle block style games but would be very difficult.

Consider this game as a relaxing practice tool to test the limits of what you can think of when you have all the time in the world to get it right!

Also, the game allows saving and loading replays. Keypresses are stored into a file named omovelog.txt ever time the game is run. If the file is renamed to imovelog.txt , the game will detect it and attempt to read commands from it.

Same replay file will always result in the exact same results because there is no randomness built into the game at all! This is the secret of how I make my incredible videos on my YouTube and Tiktok accounts.

Not everyone knows how to play my game because the controls are not mentioned in the game itself and you are expected to read this readme file because it takes a lot less effort on my part to write all about it here than program more text into the game.

Updates

November 2 2022:
I added T Spin Triple support to Chaste Tris. Only T blocks are allowed to do this stupid rotation to match SRS rotation rules. However, all other blocks remain the same. This was meant to test the Infinite TST loop invented by Massi4h. You can read more about that loop here: https://harddrop.com/wiki/Infinite_TST
