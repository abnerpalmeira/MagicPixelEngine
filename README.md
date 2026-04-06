# MagicPixel Engine

A SDL2 based game engine focused on simulating all pixels on the screen.

[Video](https://youtu.be/nBHppr3_gmI)

## Dependencies

- [SDL2]
- [SDL2_image]
- [SDL2_ttf]
- [CMake] (>= 3.23.2)

## Getting Started

### macOS
1. Install Homebrew (if not already installed).
2. Install dependencies:
   ```bash
   brew install sdl2 sdl2_image sdl2_ttf cmake
   ```

## Build and Run

We provide a convenience script to automate the build process:

```bash
chmod +x build.sh
./build.sh
```

Alternatively, you can build manually:
```bash
mkdir build && cd build
cmake ..
make
./app/MagicPixelEngine
```

## Controls

- Press **tab** to open/close UI.
- Press **R** to enable/disable Debug mode.
- Mouse wheel to increase/decrease pixel brush.

## Contributing
Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.

## License
[MIT](https://choosealicense.com/licenses/mit/)

[SDL2]: https://www.libsdl.org
[SDL2_image]: https://www.libsdl.org/projects/SDL_image
[SDL2_ttf]: https://www.libsdl.org/projects/SDL_ttf
[CMake]: https://cmake.org/
