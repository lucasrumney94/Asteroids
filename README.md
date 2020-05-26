# Asteroids
A tribute to the game _Asteroids (1979)_ in our Game Engine written in C++ using GLFW, GLM, and GLEW.

![ProjectGif](/images/shootingAsteroids.gif)


## Build
To build this project in Visual Studio 2019:

  1: Open the Property Manager window under View -> Other Windows
  
  2: Expand the root item and right-click on Debug|Win32 -> Add Existing Property Sheet
  
  3: Select the OpenGL-PropertySheet.props file in the project directory
  
  4: Do the same thing for Release|Win32
  
If you get the warning:

  warning LNK4098: defaultlib \<library\> conflicts with use of other libs; use /NODEFAULTLIB:library
  
Open the project properties window, go to Linker -> Input -> Ignore Specific Default Libraries and add the conflicting library

## Authors
Hardy Whitney
Lucas Rumney
Cody Stough

## Attribution

### Template
Used the template established in our [OpenGL Development Template](https://github.com/htw6174/OpenGL-Template).

### Entity Component System Structure
ECS Structure based heavily on Austin Morlan's [amazing article](https://code.austinmorlan.com/austin/ecs).



