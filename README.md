# Game of Life Simulation

This project is a Conway's Game of Life simulator built using the Raylib library in C++. It allows you to interact with the grid, toggle between keyboard and mouse modes, draw various shapes, and control the simulation speed. Additionally, you can clear the grid, generate random configurations, and pause or resume the simulation.

## How to Play

### Controls:

The game supports both **keyboard** and **mouse** interaction. Here's how you can control the simulation:

#### Keyboard/Mouse Modes:

- **`K` Key**: Toggle between `keyboard mode` and `mouse mode`.
    - **Keyboard Mode**: You can move a cursor on the grid using arrow keys to place or modify cells.
    - **Mouse Mode**: Use your mouse to interact directly with the grid.

#### Movement in Keyboard Mode:

- **Arrow Keys**: Move the cursor (represented by a cell-sized square) in the grid.
- **`J` Key**: Place the currently selected shape (or toggle a cell if no shape is selected).

#### Shapes:

You can select from different predefined shapes to draw on the grid:

- **`G` Key**: Select/deselect Glider.
- **`H` Key**: Select/deselect Heart shape.
- **`E` Key**: Select/deselect Eater.
- **`Q` Key**: Select/deselect Glider Gun.
- **`N` Key**: Select/deselect Not Gate.

Once a shape is selected, it will follow your cursor, and you can place it on the grid using **mouse click** (mouse mode) or **`J` key** (keyboard mode).

- **`R` Key**: Rotate the shape by 90 degrees each press (when in a shape selection mode).

#### Simulation Controls:

- **`Enter` Key**: Start the simulation.
- **`Right Shift` Key**: Pause the simulation.
- **`C` Key**: Clear the grid.
- **`P` Key**: Populate the grid with a random pattern.
- **`F` Key**: Increase the simulation speed (frames per second).
- **`S` Key**: Decrease the simulation speed.

#### Special Speed Controls:

- **`Left Shift` Key**: Temporarily speed up the simulation to max speed.
- **`Left Control` Key**: Temporarily slow down the simulation to minimum speed.

#### Typing Mode:

- **`Tab` Key**: Toggle typing mode.
  - In this mode, the keyboard is used to type or create special shapes based on alphebetic inputs on the grid, rather than for controlling the cursor.

### System Requirements

- **Operating System**: Linux, macOS, or Windows.
- **Compiler**: You need a C++ compiler (G++ or equivalent) that supports C++11 or later.
- **Raylib**: The game uses Raylib for rendering, so it needs to be installed and linked.