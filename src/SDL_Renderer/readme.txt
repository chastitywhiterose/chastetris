This folder contains a modernized version of the SDL port of Chaste Tris.

This version of Chaste Tris uses an entirely new rendering engine. It uses the hardware accelerated renderer instead of surfaces. As such it is not exactly a sequel but will contain more features than the previous version. This was one of the major features added to SDL2 compared to SDL1 which had only surfaces. I like surfaces but I wrote this to take advantage of the huge speed benefit of the new renderer. It also required a new version of my font library.

For more information see the SDL wiki here:
https://wiki.libsdl.org/SDL2/CategoryRender
