# Drone Simulator

A simple OpenGL-based drone simulator for educational use.  
This project renders a 3D drone model in a virtual environment, with camera controls and a telemetry HUD.

**GitHub Repository:**  
[https://github.com/stefan-sci/drone-control-PA](https://github.com/stefan-sci/drone-control-PA)

---

## Features

- **3D Drone Model:** Realistic drone rendered with textures.
- **Camera Controls:** Move and look around the scene using keyboard and mouse.
- **Drone Controls:** Fly the drone with keyboard input (move, ascend/descend, yaw).
- **HUD:** Displays telemetry such as altitude, speed, battery, and GPS coordinates.
- **Clean Codebase:** Minimal, easy to understand, and ready for student projects.

---

## Controls

| Key        | Action                |
| ---------- | --------------------- |
| W/A/S/D    | Move camera           |
| Mouse      | Look around           |
| Scroll     | Zoom camera           |
| UP/DOWN    | Drone forward/back    |
| LEFT/RIGHT | Drone yaw left/right  |
| SPACE      | Drone ascend          |
| LEFT SHIFT | Drone descend         |
| ESC        | Quit                  |

---

## Build & Run

### Requirements

- CMake (3.10+ recommended)
- C++17 compiler (GCC, Clang, or MSVC)
- OpenGL 3.3+
- GLFW
- GLAD
- stb_image

---

### Building on macOS

1. **Install dependencies** (if you don't have them):
    ```sh
    brew install cmake glfw
    ```
2. **Clone the repository and build:**
    ```sh
    git clone https://github.com/stefan-sci/drone-control-PA.git
    cd drone-control-PA
    mkdir build
    cd build
    cmake ..
    make
    ./DroneMonitor
    ```
3. **Notes:**
   - If you get errors about OpenGL, make sure you are using a compatible version of Xcode and have Command Line Tools installed.
   - On Apple Silicon, you may need to run the app with Rosetta if using x86_64 dependencies.

---

### Building on Windows (Visual Studio)

1. **Install [CMake](https://cmake.org/download/)** and [Visual Studio](https://visualstudio.microsoft.com/) (with Desktop development with C++ workload).
2. **Clone the repository and build:**
    ```sh
    git clone https://github.com/stefan-sci/drone-control-PA.git
    cd drone-control-PA
    mkdir build
    cd build
    cmake .. -G "Visual Studio 17 2022"  # or your installed version
    cmake --build . --config Release
    .\Release\DroneMonitor.exe
    ```
3. **Notes:**
   - If you get errors about missing DLLs, ensure GLFW and other dependencies are found by CMake or placed in your PATH.
   - You may need to install [GLFW binaries](https://www.glfw.org/download.html) and set the `GLFW_ROOT` environment variable or copy the DLLs to your build directory.

---

### Building on Windows (MinGW-w64)

1. **Install [MinGW-w64](https://www.mingw-w64.org/) and [CMake](https://cmake.org/download/)**.
2. **Clone the repository and build:**
    ```sh
    git clone https://github.com/stefan-sci/drone-control-PA.git
    cd drone-control-PA
    mkdir build
    cd build
    cmake .. -G "MinGW Makefiles"
    mingw32-make
    DroneMonitor.exe
    ```
3. **If cross-compiling from macOS/Linux:**  
   - Install `mingw-w64` (`brew install mingw-w64` or `sudo apt-get install mingw-w64`).
   - Use a toolchain file (see `mingw-w64-toolchain.cmake` in this repo):
     ```sh
     cmake .. -DCMAKE_TOOLCHAIN_FILE=../mingw-w64-toolchain.cmake -G "Unix Makefiles"
     make
     ```
   - Copy the resulting `.exe` and any required DLLs to your Windows machine.

---

### CMakeLists.txt

This project uses a `CMakeLists.txt` file to manage the build.  
All dependencies (GLFW, GLAD, stb_image) should be either included as source or linked as libraries.  
If you add new source files, update `CMakeLists.txt` accordingly.

---

## Project Structure
src/ # Source code (C++)
main.cpp
renderer.h
model.cpp
drone.h
camera.h
external/stb/ # External libraries (e.g., stb_image)
stb_image.h
shaders/ # GLSL shaders
models/drone/ # Drone model (.obj, .mtl, textures)
CMakeLists.txt # CMake build script

---

## Customization

- **Drone Model:** Replace the OBJ/MTL/textures in `models/drone/` to use your own drone.
- **Background Color:** Change `glClearColor` in `src/main.cpp` for a different background.
- **HUD:** Edit `src/hud.h` and `src/hud.cpp` to customize telemetry display.

---

## License

MIT License.  
Feel free to use and modify for educational purposes!

---

## Credits

- [GLFW](https://www.glfw.org/)
- [GLAD](https://glad.dav1d.de/)
- [stb_image](https://github.com/nothings/stb)

---

## Contact

For questions or contributions, open an issue or pull request on GitHub.

