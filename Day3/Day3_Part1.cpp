#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>

using namespace std;

int main() {
  string input;
  int lowerXBound = 0;
  int upperXBound = 0;
  int lowerYBound = 0;
  int upperYBound = 0;
  int currentX = 0;
  int currentY = 0;
  int numHousesVisited = 0;
  int gridWidth, gridHeight, numHousesInGrid;
  int* houses;
  ifstream myfile ("Day3_input");
  getline(myfile, input);
  myfile.close();

  // Find how wide and tall the grid must be at most. Arbitrarily deciding the starting location house = 0,0 for grid construction
  for(string::iterator c = input.begin(); c != input.end(); ++c) {
    switch(*c) {
      case '<':
        --currentX;
        if(currentX < lowerXBound) {
          lowerXBound = currentX;
        }
        break;
      case '>':
        ++currentX;
        if(currentX > upperXBound) {
          upperXBound = currentX;
        }
        break;
      case '^':
        ++currentY;
        if(currentY > upperYBound) {
          upperYBound = currentY;
        }
        break;
      case 'v':
        --currentY;
        if(currentY < lowerYBound) {
          lowerYBound = currentY;
        }
        break;
      default:
        cout << "ERROR1" << endl;
        break;
    }
  }

  gridWidth = upperXBound - lowerXBound + 1; // +1 because it if it goes from x=-1 to x=1, it's 3 wide and 1 - -1 = 2.
  gridHeight = upperYBound - lowerYBound + 1;

  numHousesInGrid = gridWidth*gridHeight;

  houses = (int*)calloc(numHousesInGrid,sizeof(int));

  // Starting point - start at (width-highestX, height-highestY)
  // Subtract 1 because width is 1-indexed and coordinates are 0-indexed.
  currentX = gridWidth - upperXBound - 1;
  currentY = gridHeight - upperYBound - 1;
  *(houses + (currentX) + (gridWidth * currentY)) = 1;

  for(string::iterator c = input.begin(); c != input.end(); ++c) {
    switch(*c) {
      case '<':
        --currentX;
        break;
      case '>':
        ++currentX;
        break;
      case '^':
        ++currentY;
        break;
      case 'v':
        --currentY;
        break;
      default:
        cout << "ERROR2" << endl;
        break;
    }
    *(houses + (currentX) + (gridWidth * currentY)) = 1;
  }

  // Count the number of 1s in *houses

  for(int i = 0; i < numHousesInGrid; ++i) {
    if(*(houses + i) > 0) {
      ++numHousesVisited;
    }
  }

  cout << "Number of houses visited: " << numHousesVisited << endl;

  free(houses);
  return 0;
}