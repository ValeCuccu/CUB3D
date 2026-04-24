*This project has been created as part of the 42 curriculum by VACUCCU, ANPASTAC.*

# CUB3D

## Description
CUB3D is a graphical project that explores the foundations of pseudo-3D rendering. The goal of this project is to create a first-person perspective view of a maze-like environment using the Raycasting technique. Starting from a 2D map grid, the engine calculates the distance to the nearest walls for each vertical slice of the screen, rendering them with perspective and textures to simulate a three-dimensional space.

## Instructions
This project includes both a mandatory version and a bonus version with additional features.

### Compilation
To compile the mandatory version, run the following command in the root of the repository:
`make`

To compile the bonus version (which includes features such as sprites, floor/ceiling textures, or a minimap), run:
`make_bonus`

### Execution
Once compiled, you can launch the program by providing a map file with the `.cub` extension:

**Mandatory:**
`./cub3d path/to/map.cub`

**Bonus:**
`./cub3d_bonus path/to/map_bonus.cub`

## Resources
* [Lode's Raycasting Tutorial](https://lodev.org/cgtutor/raycasting.html) - Fundamental logic for the raycasting engine.
* [MinilibX Documentation](https://harm-smits.github.io/42docs/libs/minilibx) - Reference for the graphical library used.
* [DDA Algorithm](https://en.wikipedia.org/wiki/Digital_differential_analyzer_(graphics_algorithm)) - Logic used for wall collision detection.

**AI Usage:**
Artificial Intelligence was used as a support tool during development for the following tasks:
* **Code Generation:** Writing repetitive boilerplate functions and basic structures to optimize development time.
* **Conceptual Learning:** Explaining the mathematical foundations and the deeper logic of the Raycasting algorithm and the DDA (Digital Differential Analyzer) process.

## Features (Bonus)
The `cub3d_bonus` version includes:
* Support for a separate build system via `make_bonus`.
* Additional graphical or gameplay enhancements as specified in the project requirements.