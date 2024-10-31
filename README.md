# Game of Life

**Author:** Jeremi Torój  
**Date:** 21.02.2024

### **test**

## Requirements
The program was written on Linux Ubuntu 22.04, so it should work on macOS.
If you are using windows, running it might need a different approach.
To run the program successfully, ensure that you have the following prerequisites:

- Clone or download this repository.
- Have the g++ compiler installed.
- Have Python installed.
- Have Pygame installed.

## How to Run

1. Open the `main.py` file.
2. Ensure the following configurations are set:
    - Choose starting points by editing "file_name" in `START_PAIRS = "custom_points/file_name.txt"` to any file in the `custom_points` folder.
    - Make sure `BOARD_SIZE` is at least as big as the biggest component of points (automation planned).
    - Adjust `FPS` to your preferred value (higher FPS for faster board evolution).
    - Adjust `CELL_SIZE` to your preferred value (`CELL_SIZE = number of pixels, p x p`).
3. Open the terminal and navigate to cloned/downloaded repository.
4. Run the Python script using the following command:
    ```bash
    python3 main.py
    ```
    or
    ```bash
    python main.py
    ```

## Keybinds

- **Click:**
    - Press "n" to view how each generation changes frame by frame.
    - Press space to start and stop automatic calculation of new generations.

## Description

This project, developed entirely by me, implements John Conway's "Game of Life."

The game follows a simple logic:
- A dead cell with 3 neighbors becomes alive.
- An alive cell with fewer than 2 neighbors dies of solitude.
- An alive cell with more than 3 neighbors dies of overpopulation.

To implement this logic, a Cursor list is used as a container for all alive cells and their neighboring dead cells. This approach optimizes performance by allowing the program to scan only the necessary cells for each generation instead of the entire board.

The main game logic and actions are encapsulated in the `GameOfLife.hpp` file, which manages the entire game. The `GameOfLife.cpp` file is responsible for running the game logic, calculating next generations, and communicating the state of the board to the `main.py` Python script through pipes for visualization.
