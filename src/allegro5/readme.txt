After having written Chaste Tris in Raylib and then SDL, I finally have also ported it to using Allegro 5.
This means that it behaves exactly like the SDL version except that all the windows, timing, graphics, and image loading were done using Allegro functions.

The rest of the code that deals with physics of the blocks is all mine and uses only the C standard library.

In any case, this makes the third Open Source multiplatform graphics API that I have used to make this same game. This gives me a chance to see where they all differ so I can have an objective opinion on the differences between SDL, Allegro, and Raylib.

What I have learned from this experience is that Allegro really is just as good as SDL in terms of what it can do. It also has superior documentation to SDL.
Neither SDL or Allegro are as easy to start with as Raylib, but I like them more because they are compatible with ANSI C, also known as C89.
