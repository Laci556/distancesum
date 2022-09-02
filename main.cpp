#include <iostream>

#include "findShortestSum.h"

int main()
{
  int m, n;
  std::cin >> m >> n;
  char **grid = new char *[m];

  // Get the grid from stdin
  for (int i = 0; i < m; i++)
  {
    grid[i] = new char[n];
    for (int j = 0; j < n; j++)
    {
      std::cin >> grid[i][j];
    }
  }

  // Calculate and print the sum of the shortest distances
  std::cout << findShortestSum(grid, m, n) << std::endl;

  return 0;
}