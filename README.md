# MagicPixel Engine

A SDL2 based game engine focused on simulating all pixels on the screen.

[Video](https://youtu.be/nBHppr3_gmI)

## Dependencies

- [SDL2]
- [SDL2_image]
- [SDL2_ttf]

## Instructions

- Press **tab** to open/close UI.
- Press **R** to enable/disable Debug mode.
- Mouse wheel to increse/descrease pixel brush.

## Contributing
Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.

## License
[MIT](https://choosealicense.com/licenses/mit/)

[SDL2]: https://www.libsdl.org
[SDL2_image]: https://www.libsdl.org/projects/SDL_image
[SDL2_ttf]: https://www.libsdl.org/projects/SDL_ttf

## Building a Windows executable with Docker

You can cross compile the engine for Windows using the provided Dockerfile. First install Docker, then run the following commands from the project root:

```bash
docker build -t magicpixel-builder .
docker run --rm -v $(pwd):/build magicpixel-builder
```

The resulting `.exe` can be found in `build/app/Release/` inside the container or in the mounted `build` directory.
