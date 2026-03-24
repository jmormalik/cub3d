# cub3D

*This project has been created as part of the 42 curriculum by jaemyu and inhlee.*

## Description

cub3D is a 3D graphical representation project inspired by the world-famous 1992 game, Wolfenstein 3D. Developed as part of the core curriculum at 42 Gyeongsan, the primary goal of this project is to explore the concept of raycasting by creating a dynamic, first-person view inside a maze. 

Written in C and utilizing the `minilibx` library, this project delves into the mathematics of computer graphics. It implements the Digital Differential Analyzer (DDA) algorithm to calculate wall intersections, processes map parsing to load textures and colors, and handles real-time user inputs for movement and camera rotation. Through this project, we explore fundamental game engine mechanics, memory management, and rendering optimization.

## Instructions

### Compilation
To compile the project, navigate to the root directory of the repository and run:
```bash
make
This will compile the source files and generate the cub3D executable.

Execution
Run the program by passing a valid .cub map file as an argument:
./cub3D maps/map.cub
Controls
W / A / S / D: Move forward, left, backward, and right.

Left / Right Arrow Keys: Rotate the camera view left or right.

ESC (or Red Cross): Safely exit the game and close the window.

Resources
References & Documentation:

Lodev's Raycasting Tutorial: The primary mathematical reference used for implementing the DDA algorithm, camera plane concepts, and texture mapping calculations.

minilibx documentation and internal man pages for understanding image buffers and event hooks.

AI Usage:
Artificial Intelligence (Gemini) was utilized during the development of this project for the following specific tasks:

Mathematical Debugging: Verifying and refining the DDA algorithm logic, specifically fixing coordinate offsets and ensuring exact wall_x calculations to prevent texture distortion.

Texture Mapping Optimization: Assisting in the implementation of bitwise AND operations (&) over modulo (%) for faster texture Y-coordinate extraction, and guiding the transition from mlx_pixel_put to a custom image buffer implementation to eliminate flickering.

Norminette Compliance & Refactoring: Restructuring complex parsing functions (like data_find) and rendering loops to strictly adhere to the 42 Norm (25 lines per function, max 5 variables, naming conventions).

Performance Optimization: Advising on the shift from a polling rendering model (mlx_loop_hook) to an event-driven model using update flags, drastically reducing CPU usage and overheating.
