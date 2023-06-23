Chaste Tris 2
Also known as Chaste Tris: SDL_Renderer

This project is a modernized version of the SDL port of Chaste Tris. The original version which was written with SDL is a perfect Tetris game, and is itself ported from my first version written with Raylib.
However, it was made using only software rendering by use of the SDL_Surface structure. This is a perfectly good way to do a simple Tetris style game. However I wanted to challenge myself by learning to use the modern textures and renderer that SDL2 provides.

This version of Chaste Tris uses an entirely new rendering engine. It uses the hardware accelerated renderer instead of surfaces. As such it is not exactly a sequel but will contain more features than the previous version. This was one of the major features added to SDL2 compared to SDL1 which had only surfaces. I like surfaces but I wrote this to take advantage of the huge speed benefit of the new renderer. It also required a new version of my font library, which has been rewritten to use textures instead of surfaces.

My initial name I thought up for this project was Chaste Tris 2. This is because it is based on SDL version 2 and also because it is not the original Chaste Tris game. The original is published on Steam and was written using Raylib. It works a lot like this version but also contains music and fancy animations I added to make it look cool.

To support my programming work, please buy the original version on either Steam or itch.io

https://store.steampowered.com/app/1986120/Chaste_Tris/
https://chastitywhiterose.itch.io/chaste-tris

In the future I hope to write a more detailed guide on the controls and how to play it. But really all you need to know to get started is:

WASD or arrow keys move the block
Z and X rotate it
and C holds the block for later use. It can be swapped infinite times with the current block.

The game also has the ability to save and load at any point in time. This is a neat feature that I have shown in some of my videos. Please contact me if you want to know more:

chastitywhiterose@gmail.com

I have also added some basic fullscreen support and I am not sure exactly what option will be used to enable it or if it will just be the default option.

