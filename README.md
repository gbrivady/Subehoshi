# Subehoshi

A 2D gravity simulator, written in C and CUDA, using a RK4 integration method.

## Features

Displays a bunch of objects with the same mass, all interacting with each others.

Number of objects to run in the simulation can be passed as command line argument.

## Planned Features

- A nice GUI, a better Camera, better displaying, and 3D

- Optimising the CUDA application

## Compilation

The project was built using CMake.

Two targets are provided : appCPU and appCUDA. First one is a CPU-only app, while the second one is the CUDA version.

Compilation of the CPU app was tested on Windows using MSVC Version 19.30.30709 for x64 and the mingw64 release of gcc, version 11.2.0, but it should work just fine in Linux too.

Compilation of the CUDA app was tested on Windows using the same version of MSVC and Cuda compilations tools release 11.6, and builds for architecture 7.0 .

Compiled binaries will be in the bin directory.

## Requirements

### Common

- CMake 3.18.0+
- SDL 2.0.20+

### CUDA app

- a working version of the Cuda compilation tools
- a CUDA card of compute capability >= 6.0 (support of atomicAdd on double values), aka Pascal architecture (GeForce 10 Series, Quadro P400-P6000, Quadro GP100,  Tesla P4-P100) or newer (Volta, Turing, Ampere)
