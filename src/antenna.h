/**
 * @file antenna.h
 * @author Ricardo Araújo (a21150@alunos.ipca.pt)
 * @brief Header file for antenna.c.
 * @version 0.1
 * @date 18-05-2025
 *
 * @copyright Copyright (c) 2025
 *
 */

#include "includes.h"

Antenna *CreateAntenna(AntennaData values);
Antenna *InsertAntenna(Antenna *graphHead, Antenna *newNode);
Antenna *InsertAntennaSorted(Antenna *graphHead, Antenna *newNode);
Antenna *RemoveAntenna(Antenna *graphHead, Antenna *target);
Antenna *FindAntenna(Antenna *graphHead, int x, int y);
Antenna *DestroyAntennas(Antenna *graphHead);

Adjacency *CreateAdjacency(AntennaData values, Antenna *original);
Adjacency *InsertAdjacency(Adjacency *adjHead, Adjacency *newNode);
Adjacency *InsertAdjacencySorted(Adjacency *adjHead, Adjacency *newNode);
Adjacency *RemoveAdjacency(Adjacency *adjHead, Adjacency *target);
Adjacency *FindAdjacency(Adjacency *adjHead, int x, int y);
Adjacency *DestroyAdjacencies(Adjacency *adjHead);
bool AreAdjacent(Antenna *a, Antenna *b);

bool GenerateAdjacencies(Antenna *graphHead);
bool RemoveOtherAdjacencies(Antenna *graphHead, Antenna *target);
