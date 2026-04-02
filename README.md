# cub3d

A 42 project focused on building a simple 3D maze renderer with **raycasting**.  
The program reads a `.cub` configuration file, loads textures and colors, parses the map, and displays a first-person view using the **MiniLibX**.

# Cub3d Project Overview

## What the project does

- reads and validates a `.cub` file
- loads wall textures and floor/ceiling colors
- parses the map and player start position
- renders a 3D scene with raycasting
- handles player movement and rotation

## Main challenges

This project was mostly about combining parsing with graphics.

The parts that took the most work were:
- organizing and validating the `.cub` file
- handling map errors correctly
- learning how to draw with MiniLibX
- understanding raycasting and DDA
- applying textures to walls
- managing memory and cleanup on errors

## Parsing

The parser needs to reject invalid files and exit cleanly.

Some important checks are:
- duplicated or missing texture identifiers
- invalid RGB values
- wrong map characters
- more than one player or no player
- open maps / maps not surrounded by walls
- invalid texture paths

A big part of the project is not just reading the file, but making sure every possible bad input is handled safely.

## MiniLibX

MiniLibX is used to create the window and draw the image.

Instead of drawing pixel by pixel directly to the window, I used an image buffer, updated its pixels, and then displayed the final image. This is much more efficient and makes the rendering loop easier to manage.

It was also important to understand:
- image buffers
- pixel colors
- keyboard hooks
- window events
- refreshing the frame continuously

## Raycasting

The rendering is based on **raycasting**.

For each vertical column of the screen, a ray is sent from the player’s position into the map.  
The distance to the first wall hit is calculated, and that distance determines how tall the wall slice should appear on screen.

This creates the 3D effect from a 2D map.

Main ideas involved:
- field of view
- horizontal and vertical intersections
- DDA stepping
- perpendicular wall distance
- fisheye correction
- wall strip projection

## Textures

After finding the wall hit, the program chooses the correct texture depending on the wall direction.

Then it calculates which column of the texture should be drawn for that screen stripe.  
This is what gives each wall its detailed look instead of just flat colors.

## What I learned

This project helped me improve a lot in:
- file parsing
- error handling
- struct organization
- graphics basics
- mathematical reasoning
- low-level rendering logic
