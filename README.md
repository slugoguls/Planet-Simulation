🌍 Planetary Simulation using C++ & OpenGL

A real-time, interactive 3D simulation that visualizes gravitational interactions between celestial bodies. Built with C++, OpenGL, and GLM, this project offers a physics-accurate and scalable system for simulating planetary motion using Newtonian mechanics.

🧠 Project Overview

This simulation models gravitational attraction between multiple planets in 3D space. It calculates the net gravitational force on each planet based on the masses and distances of all other planets and updates their velocity and position accordingly. All rendering is handled using OpenGL, with support from GLFW for window/context management and GLM for math operations.

🧮 Physics Calculations

The simulation uses Newton's Law of Universal Gravitation:

F=G⋅ m1*m2/ r * r
​

Where:

- 𝐹 is the gravitational force between two bodies

- 𝐺 is the gravitational constant

- m1, m2 are the masses of the two bodies

- 𝑟 is the distance between them

Each simulation frame:

- Computes the force vector exerted on each body by all others

- Applies Newton Second Law F = m⋅a to find acceleration

- Integrates acceleration to update velocity

- Integrates velocity to update position

- Velocity Verlet or semi-implicit Euler integration may be used for numerical stability.
 
​🖥 Rendering

- Each planet is rendered as a shaded 3D sphere

- The view can include rotation, zoom, or camera movement

- Uses GLM for matrix transformations (model, view, projection)

- Optional glow or lighting effects can be added via shaders

 🧰 Tech Stack
 
- C++ — Core simulation and application logic

- OpenGL — 3D rendering API

- GLFW — Window/context creation and input handling

- GLM — Math library for vectors, matrices, and transformations

📦 Installation & Build

🔧 Prerequisites

- C++17 or later

- CMake

- OpenGL-compatible GPU

- GLFW and GLM

🛠 Build Instructions

```
git clone https://github.com/slugoguls/planet-simulation.git

cd planet-simulation

mkdir build && cd build

cmake ..

make

./PlanetSim

```
💡 Tip: If using Visual Studio or Xcode, generate appropriate project files via cmake -G.

🔄 Customization

To add your own planets:

- Open main.cpp 

- Add planets like so:

```
Planet mercury(1.0f, 0.055f, glm::vec3(5.8f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 6.55f), "Mercury");
Planet venus(1.8f, 0.815f, glm::vec3(10.8f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 4.79f), "Venus");

Planet name (radius, mass, position, velocity, label)
```

The planets in the simulation below are all red becuase they are being used as PlaceHolders

​![Sim](https://github.com/slugoguls/Planet-Simulation/blob/main/image.png?raw=true)
 
​

📄 License
 
MIT License — feel free to use, modify, and share with attribution.
