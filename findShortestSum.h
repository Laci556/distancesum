#pragma once
#include <iostream>
#include <vector>

/// Represents a "Node" in the grid
struct Node
{
  int distance = 0;
  bool checked = false;
  int row, col;
  char type;
  Node(char t, int r, int c) : type(t), row(r), col(c) {}
};

/**
 * Converts a char containing an uppercase hexadecimal value to int
 *
 * @param c The uppercase haxadecimal value
 * @return The int value of c
 */
inline int hexToInt(char c)
{
  return (c >= 'A') ? (c - 55) : (c - 48);
}

/// Offsets of the neighboring cells, an array of [rowOffset, colOffset] pairs
const int neighborDirections[4][2] = {{0, 1}, {-1, 0}, {0, -1}, {1, 0}};

/**
 * Returns the possible entry directions
 *
 * @param num The int value of C
 * @return [from right, from up, from left, from down]
 */
inline bool *getDirections(int num)
{
  bool *directions = new bool[4];
  directions[0] = (bool)(num & 1);
  directions[1] = (bool)(num & 2);
  directions[2] = (bool)(num & 4);
  directions[3] = (bool)(num & 8);
  return directions;
}

/**
 * Returns whether the given row and column values are inside the grid
 *
 * @param m Rows of the grid
 * @param n Columns of the grid
 * @param r Row to be checked
 * @param c Col to be checked
 */
inline bool validCoords(int m, int n, int r, int c) { return (r >= 0) && (r <= m - 1) && (c >= 0) && (c <= n - 1); }

/**
 * Returns the sum of the shortest paths from the start to all 'C' nodes.
 *
 * The function calculates the distance to all possible nodes in the grid,
 * finds the 'C' nodes and sums their minimum distances.
 *
 * @param grid 2-dimensional char array
 * @param m Number of rows
 * @param n Number of columns
 */
int findShortestSum(char **grid, int m, int n);