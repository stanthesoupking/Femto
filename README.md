# Femto
WIP virtual operating system designed for touch interfaces and low-end devices. It is currently being designed on a  Raspberry Pi 3b+, utilising an 800 x 480 pixel, 5-inch display module.
## Compiling
Before compiling you will need to install the following dependencies:
* CMake
* SDL 2.0
* SDL_image 2.0
* SDL_ttf 2.0
### Release Build
```
mkdir release
cd release
cmake ../ -DCMAKE_BUILD_TYPE=Release
make
```
### Debug Build
```
mkdir debug
cd debug
cmake ../ -DCMAKE_BUILD_TYPE=Debug
make
```