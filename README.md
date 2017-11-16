## About TheRestlessTombs
The Restless Tombs is my first c++/OpenGL game made in my own framework tb2d
Gameplay video: https://www.youtube.com/watch?v=2CB5YxnFJQ0

## Compiling

You can use cmake to create the project files.

I have only tested my game on ubuntu and @rutgerklamer tested it on arch linux for me, so if you are using something else there is no guarentee it will work.
Also you will need to install the sdl2 package if you are on ubuntu run this in the terminal
"sudo apt-get install libsdl2-2.0-0 libsdl2-ttf-2.0-0 libsdl2-image-2.0-0 libsdl2-mixer-2.0-0 libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev libsdl2-mixer-dev".

On arch linux you need to install other sdl2 packages too, You can run "sudo pacman -S sdl2 sdl2_image sdl2_ttf sdl2_mixer"

## Documentation

Documentation of the code can be viewed by running this command "doxygen Doxyfile" in the root of the folder.
It will create a documentation folder and then you have too search for index.html and open it.

## Libraries

- tb2d: <https://github.com/TimBunk/tb2d>
- glew: <http://glew.sourceforge.net/>
- sdl2: <https://www.libsdl.org/>
- sdl2-ttf <https://www.libsdl.org/projects/SDL_ttf/>
- sdl2-image <https://www.libsdl.org/projects/SDL_image/>
- sdl2-mixer <https://www.libsdl.org/projects/SDL_mixer/>
- glm: <http://glm.g-truc.net/0.9.8/index.html>
- SOIL2: <https://bitbucket.org/SpartanJ/soil2>
- box2d: <http://box2d.org/>