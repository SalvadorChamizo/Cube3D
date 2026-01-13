# Cube3D

Cube3D is a 3D raycasting game written in C that uses MLX42 for windowing and rendering. It implements a map parser, texture loading, and a raycasting renderer to produce a first-person view based on .cub maps.

## Key Features
- Raycasting renderer with texture mapping and configurable FOV and resolution ([include/cub3d.h](include/cub3d.h))
- Robust map parsing and validation with clear error handling ([src/parser/parser.c](src/parser/parser.c), [`map_size`](src/parser/get_map_utils.c))
- Texture and color handling with PNG support via MLX42's lodepng integration ([MLX42/README.md](MLX42/README.md))
- Modular codebase: `parser`, `raycasting`, `game`, and `print_and_textures` subsystems
- Build automation with Makefile and integration with the MLX42 subproject ([Makefile](Makefile))

## Tech Stack
- Language: C (Clang compatible)
- Graphics / Windowing: MLX42 (OpenGL + GLFW) — see [MLX42/README.md](MLX42/README.md)
- Utility library: custom libft ([libft/Makefile](libft/Makefile))
- Build: Make, CMake (for MLX42), GNU toolchain
- Image handling: lodepng (included with MLX42)

## Architecture & Design
- Clear separation of concerns:
  - Parser: validates and constructs in-memory map representation ([src/parser/*](src/parser/))
  - Raycasting: computes visible geometry and texture coordinates ([src/raycasting/*](src/raycasting/))
  - Game logic: player movement and input handling ([src/game/*](src/game/))
  - Textures/Rendering: loads images and pushes to window via MLX42 ([src/print_and_textures/*](src/print_and_textures/))
- Global types and configuration in [include/cub3d.h](include/cub3d.h)
- Small, focused modules to simplify testing and maintenance (examples: [`ft_remove_nl`](src/parser/check_utils.c), [`map_size`](src/parser/get_map_utils.c))

## Getting Started

### Prerequisites
- Linux or macOS (assumed)
- clang or gcc, make, cmake
- GLFW development packages (for MLX42)
- X11 / Wayland development headers as applicable

### Installation
1. Build MLX42 (required for linking):
```bash
# Option A: using MLX42's CMake build
cmake -B MLX42/build MLX42 && cmake --build MLX42/build --parallel
```
Refer to [MLX42/README.md](MLX42/README.md) for platform-specific details.

2. Build the project:
```bash
# From repository root
make
```
This builds libft, the MLX42 dependency (if configured), and the `cub3D` binaries.

### Running the project
- Run the main executable with a .cub map file from the `maps/` folder:
```bash
./cub3D maps/map1.cub
# or run the bonus build
./cub3D_bonus maps/map1.cub
```

## Usage
- The game accepts a single map file in `.cub` format. Example maps are in [maps/](maps/).
- Common controls and behaviour are implemented in the game module; see [src/game/game_move.c](src/game/game_move.c) for input bindings (assumed WASD movement and look control; verify actual key bindings in code).

## What I Learned / Technical Challenges
- Integrating MLX42 and lodepng for safe texture loading and cross-platform rendering.
- Designing a resilient map parser (handling newlines, format validation and error reporting — see [`ft_remove_nl`](src/parser/check_utils.c) and parser validation utilities).
- Implementing a performant raycasting pipeline with correct texture sampling and perspective correction ([src/raycasting/*](src/raycasting/)).
- Managing a mixed build system (Make + CMake) and ensuring deterministic artifacts for CI and local builds.

## Future Improvements
- Add unit and integration tests and CI (target testable parser and raycaster components).
- Improve CLI and runtime diagnostics (verbose parsing errors and map visualizer).
- Optimize rendering path and add optional multi-threaded precomputation for larger maps.
- Expand supported image formats and add a fallback loader.

## Author & Contact
- Authors: schamizo, saroca-f
- Contact: salvadorchamizo@gmail.com, saroca1993@gmail.com

For implementation details, start with the entry point [src/main.c](src/main.c), and consult [Makefile](Makefile) and [include/cub3d.h](include/cub3d.h) for build and configuration constants.