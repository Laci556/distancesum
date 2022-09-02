#include "findShortestSum.h"
#include <vector>

int findShortestSum(char **grid, int m, int n)
{
  // Create nodes for all the cells in the grid
  Node ***distances = new Node **[m];
  int startRow, startCol;
  for (int i = 0; i < m; i++)
  {
    distances[i] = new Node *[n];
    for (int j = 0; j < n; j++)
    {
      distances[i][j] = new Node(grid[i][j], i, j);
      if (grid[i][j] == 'T')
      {
        startRow = i;
        startCol = j;
      }
    }
  }

  // Keep track of nodes to be checked
  std::vector<Node *> nodesToCheck;
  // Start with the start node
  nodesToCheck.push_back(distances[startRow][startCol]);

  // Keep calculating distances until there is no nodes left to check
  while (!nodesToCheck.empty())
  {
    // Get the last node and set its state to checked
    Node *current = nodesToCheck[nodesToCheck.size() - 1];
    current->checked = true;
    nodesToCheck.pop_back();

    // Calculate the distance to all neighboring nodes
    for (int i = 0; i < 4; i++)
    {
      int r = current->row + neighborDirections[i][0];
      int c = current->col + neighborDirections[i][1];

      if (validCoords(m, n, r, c))
      {
        Node *neighbor = distances[r][c];
        if (neighbor->type != '-')
        {
          // Skip non free nodes
          neighbor->checked = true;
        }
        else
        {
          // The distance to the neighbor is the current node's distance + 1
          int newDistance = current->distance + 1;
          // If the neighbor hasn't been checked or a shorter path is found, set the new distance
          // and push it to the vector so that the neighbor's neighbors get recalculated
          if (!neighbor->checked || (newDistance < neighbor->distance))
          {
            neighbor->distance = newDistance;
            neighbor->checked = true;
            nodesToCheck.push_back(neighbor);
          }
        }
      }
    }
  }

  int sum = 0;
  // Find all the 'C' nodes
  for (int i = 0; i < m; i++)
  {
    for (int j = 0; j < n; j++)
    {
      Node *node = distances[i][j];
      if (node->type != '-' && node->type != 'X' && node->type != 'T')
      {
        int shortestFromStart = 0;
        bool foundRoute = false;
        // Get the int value of the node
        int hexValue = hexToInt(node->type);
        // Calculate the valid directions to enter
        bool *directions = getDirections(hexValue);
        // Loop through the neighboring nodes
        for (int k = 0; k < 4; k++)
        {
          int nRow = node->row + neighborDirections[k][0];
          int nCol = node->col + neighborDirections[k][1];

          // Check if neighboring coords are within the grid and the 'C' node can be entered from that direction
          if (directions[k] && validCoords(m, n, nRow, nCol))
          {
            // If the neighbor node is the start set the distance to 0 and exit the loop
            if (distances[nRow][nCol]->type == 'T')
            {
              shortestFromStart = 0;
              break;
            }
            // If the neighbor is a free node and it has been checked (= has a path to the start)
            // and it's the shortest path found set its distance as the shortest path from start
            else if (distances[nRow][nCol]->type == '-' && distances[nRow][nCol]->checked && (!foundRoute || distances[nRow][nCol]->distance < shortestFromStart))
            {
              foundRoute = true;
              shortestFromStart = distances[nRow][nCol]->distance;
            }
          }
        }
        // Free the momory for directions array
        delete directions;
        sum += shortestFromStart;
      }
    }
  }

  // Free the memory for distances matrix
  for (int i = 0; i < m; i++)
  {
    for (int j = 0; j < n; j++)
    {
      delete distances[i][j];
    }
    delete distances[i];
  }
  delete distances;

  return sum;
}
