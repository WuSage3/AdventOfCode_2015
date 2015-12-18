/* Written for the C++14 compiler at "https://ideone.com/" */

#include <string>
#include <iostream>
#define GRID_SIZE 100
#define EXTENDED_GRID_SIZE GRID_SIZE+2
#define NUM_STEPS 100

using namespace std;

/* Prototypes */
void printGrid(int[EXTENDED_GRID_SIZE][EXTENDED_GRID_SIZE]);
void printGridWithDummy(int[EXTENDED_GRID_SIZE][EXTENDED_GRID_SIZE]);
int getNumNeighborsOn(int[EXTENDED_GRID_SIZE][EXTENDED_GRID_SIZE], int, int);
int countLightsOn(int[EXTENDED_GRID_SIZE][EXTENDED_GRID_SIZE]);

int main() {
  int currRow, currColumn, numLightsOn;
  string inputLine;
  int grid[EXTENDED_GRID_SIZE][EXTENDED_GRID_SIZE];

  currRow = 1;
  while(getline(cin, inputLine)) {
    for(string::size_type i = 0; i < inputLine.size(); ++i) {
      char currChar = inputLine[i];
      switch(currChar) {
        case '#': // On
          grid[currRow][i+1] = 1;
          break;
        case '.': // Off
          grid[currRow][i+1] = 0;
          break;
        default: // Error
          grid[currRow][i+1] = -1;
          break;
      }
    }
    ++currRow;
  }

  // Initialize the outermost dummy columns and rows to 0
  currRow = 0;
  for(int i = 0; i < EXTENDED_GRID_SIZE; ++i) {
    grid[currRow][i] = 0;
  }
  currRow = EXTENDED_GRID_SIZE-1;
  for(int i = 0; i < EXTENDED_GRID_SIZE; ++i) {
    grid[currRow][i] = 0;
  }
  currColumn = 0;
  for(int i = 0; i < EXTENDED_GRID_SIZE; ++i) {
    grid[i][currColumn] = 0;
  }
  currColumn = EXTENDED_GRID_SIZE-1;
  for(int i = 0; i < EXTENDED_GRID_SIZE; ++i) {
    grid[i][currColumn] = 0;
  }

  // Main animation loop
  for(int z = 0; z < NUM_STEPS; ++z) {
    int newGrid[EXTENDED_GRID_SIZE][EXTENDED_GRID_SIZE];

    for(int row = 1; row < EXTENDED_GRID_SIZE-1; ++row) {
      for(int column = 1; column < EXTENDED_GRID_SIZE-1; ++column) {
        int numNeighborsOn = getNumNeighborsOn(grid, row, column);
        switch(grid[row][column]) {
          case 0: // Off
            if(numNeighborsOn == 3) {
              newGrid[row][column] = 1;
            } else {
              newGrid[row][column] = 0;
            }
            break;
          case 1: // On
            if((numNeighborsOn == 2) || (numNeighborsOn == 3)) {
              newGrid[row][column] = 1;
            } else {
              newGrid[row][column] = 0;
            }
            break;
          default: // Error
            newGrid[row][column] = -1;
            break;
        }
      }
    }

    // Replace grid with newGrid
    for(int row = 1; row < EXTENDED_GRID_SIZE-1; ++row) {
      for(int column = 1; column < EXTENDED_GRID_SIZE-1; ++column) {
        grid[row][column] = newGrid[row][column];
      }
    }
  }

  numLightsOn = countLightsOn(grid);

  cout << numLightsOn << endl;
  return 0;
}

void printGrid(int grid[EXTENDED_GRID_SIZE][EXTENDED_GRID_SIZE]) {
  for(int i = 1; i < EXTENDED_GRID_SIZE-1; ++i) {
    for(int j = 1; j < EXTENDED_GRID_SIZE-1; ++j) {
      cout << grid[i][j];
    }
    cout << endl;
  }
  return;
}

void printGridWithDummy(int grid[EXTENDED_GRID_SIZE][EXTENDED_GRID_SIZE]) {
  for(int i = 0; i < EXTENDED_GRID_SIZE; ++i) {
    for(int j = 0; j < EXTENDED_GRID_SIZE; ++j) {
      cout << grid[i][j];
    }
    cout << endl;
  }
  return;
}

int getNumNeighborsOn(int grid[EXTENDED_GRID_SIZE][EXTENDED_GRID_SIZE], int x, int y) {
  int numNeighborsOn = 0;

  if(grid[x-1][y] == 1) { // Left neighbor
    ++numNeighborsOn;
  }
  if(grid[x+1][y] == 1) { // Right neighbor
    ++numNeighborsOn;
  }
  if(grid[x][y+1] == 1) { // Top neighbor
    ++numNeighborsOn;
  }
  if(grid[x][y-1] == 1) { // Bottom neighbor
    ++numNeighborsOn;
  }
  if(grid[x-1][y+1] == 1) { // Northwest neighbor
    ++numNeighborsOn;
  }
  if(grid[x+1][y+1] == 1) { // Northeast neighbor
    ++numNeighborsOn;
  }
  if(grid[x-1][y-1] == 1) { // Southwest neighbor
    ++numNeighborsOn;
  }
  if(grid[x+1][y-1] == 1) { // Southeast neighbor
    ++numNeighborsOn;
  }

  return numNeighborsOn;
}

int countLightsOn(int grid[EXTENDED_GRID_SIZE][EXTENDED_GRID_SIZE]) {
  int numLightsOn = 0;
  for(int i = 1; i < EXTENDED_GRID_SIZE-1; ++i) {
    for(int j = 1; j < EXTENDED_GRID_SIZE-1; ++j) {
      if(grid[i][j] == 1) {
        ++numLightsOn;
      }
    }
  }
  return numLightsOn;
}