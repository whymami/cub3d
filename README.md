# cub3D  
My first RayCaster with miniLibX  

## Summary  
This project is inspired by the world-famous Wolfenstein 3D game, considered the first FPS ever created.  
The goal is to make a dynamic view inside a maze, where the player must find their way using ray-casting.  
Developed entirely in C with MiniLibX, this project focuses on understanding graphical rendering, vector math, and real-time rendering logic.  

## Features  
- Ray-casting rendering engine  
- Textured walls for all directions (N, S, E, W)  
- Configurable floor and ceiling colors  
- Player movement with `W`, `A`, `S`, `D`  
- Camera rotation with arrow keys  
- Proper exit handling with `ESC` and window close button  
- Parsing of `.cub` map files for textures, colors, and map data  

## Bonus Features  
- Wall collision detection  
- Minimap system  
- Doors that open and close  
- Animated sprites  
- Mouse view rotation  

## How It Works  
1. Parses the `.cub` configuration file containing map layout, textures, and RGB colors.  
2. Uses ray-casting to calculate visible walls and their distances from the player.  
3. Renders the environment column by column in real time using MiniLibX.  
4. Handles input events to update camera direction and player movement.  

## Technologies  
- Language: C  
- Graphics Library: MiniLibX  
- Math Library: `<math.h>`  
- Build System: Makefile  
- OS: macOS / Linux  

## Example Map  
```

NO ./textures/north.xpm
SO ./textures/south.xpm
WE ./textures/west.xpm
EA ./textures/east.xpm
F 220,100,0
C 225,30,0
111111
100101
101001
1100N1
111111

