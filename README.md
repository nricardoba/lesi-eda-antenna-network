# EDA Project - Antenna Management and Adverse Effects

## Description

This project, developed for the Advanced Data Structures (Estruturas de Dados Avançadas) course, is a C application for managing an antenna network, its adjacencies, and adverse effects. It allows creating, removing, and searching antennas, generating and viewing connections, performing breadth-first (BFS) and depth-first (DFS) traversals, and analyzing adverse effects across the network.

## Features

- **Antenna Management:** Insertion, removal, search, and listing of antennas.
- **Adjacencies:** Generation and visualization of connections between antennas.
- **Adverse Effects:** Identification and visualization of adverse effects between antennas.
- **Graph Traversals:** Breadth-first search (BFS) and depth-first search (DFS) from any antenna.
- **Persistence:** Reading and writing data to binary files.
- **Terminal Interface:** Interactive menus for all operations.

## Building

To build the project, use the `makefile` provided in the `src` folder:

```sh
cd src
make
