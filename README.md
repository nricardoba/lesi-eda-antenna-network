# EDA Project - Antenna Management and Adverse Effects

## Description

This project, developed for the Advanced Data Structures (EDA) course, is a C application for managing an antenna network, its adjacencies, and adverse effects. It allows creating, removing, and searching antennas, generating and viewing connections, performing breadth-first (BFS) and depth-first (DFS) traversals, and analyzing adverse effects across the network.

**Final grade: 16/20.**

## Features

- **Antenna Management:** Insertion, removal, search, and listing of antennas.
- **Adjacencies:** Generation and visualization of connections between antennas.
- **Adverse Effects:** Identification and visualization of adverse effects between antennas.
- **Graph Traversals:** Breadth-first search (BFS) and depth-first search (DFS) from any antenna.
- **Persistence:** Reading and writing data to binary files.
- **Terminal Interface:** Interactive menus for all operations.

## Building

To build and run the project, use the `makefile` provided in the `src` folder:

```sh
cd src
make
```

To build without launching the application, run `make prog` from `src`, then use `./prog` to start it.

## Data Files

Run the application from `src`, since data file paths are relative to the working directory:

- `antennas.txt`: Text matrix containing antenna frequencies and empty cells (`.`).
- `graph.bin`: Binary antenna data, created when the graph is saved. Matrix dimensions are entered when loading this file.

The matrix uses `#` for adverse effects and `@` where an antenna and an adverse effect overlap. Coordinates are 1-based: `x` is the row and `y` is the column.

## Academic Context

Developed for the **Object-Oriented Programming** course, with a final grade of **16 out of 20**.
