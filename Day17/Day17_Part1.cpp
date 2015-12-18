/* Written for the C++14 compiler at "https://ideone.com/" */

#include <string>
#include <iostream>
#define NUM_CONTAINERS 20
#define NUM_LITERS_EGGNOG 150

using namespace std;

/* Prototypes */
int doneFlag(int*);
int getContainerCombTotalLiters(int*, int*);

int main() {
  int i;
  string inputLine;
  int containerComb[NUM_CONTAINERS]; // 1 = used, 0 = not used
  int containers[NUM_CONTAINERS];
  int combinations = 0;

  for(i = 0; i < NUM_CONTAINERS; ++i) {
    containerComb[i] = 0;
  }

  i = 0;
  while(getline(cin, inputLine)) {
    int number = atoi(inputLine.c_str());
    containers[i] = number;
    ++i;
  }

  while(doneFlag(containerComb) == 0) {
    int numLitersEggnog = getContainerCombTotalLiters(containerComb, containers);
    if(numLitersEggnog == NUM_LITERS_EGGNOG) {
      ++combinations;
    }

    // Increment combination of containers
    for(i = NUM_CONTAINERS - 1; i >= 0; --i) {
      if(containerComb[i] == 1) {
        containerComb[i] = 0;
        continue;
      } else {
        containerComb[i] = 1;
        break;
      }
    }
  }

  // Check last combination of all containers used
  int numLitersEggnog = getContainerCombTotalLiters(containerComb, containers);
  if(numLitersEggnog == NUM_LITERS_EGGNOG) {
    ++combinations;
  }

  cout << combinations << endl;

  return 0;
}

int doneFlag(int* containerComb) {
  int doneFlag = 1;
  for(int i = 0; i < NUM_CONTAINERS; ++i) {
    if(containerComb[i] != 1) { // Assuming the combination '11...111' (which all containers are used) is the final one.
      doneFlag = 0;
      break;
    }
  }
  return doneFlag;
}

int getContainerCombTotalLiters(int* containerComb, int* containers) {
  int numLiters = 0;
  for(int i = 0; i < NUM_CONTAINERS; ++i) {
    if(containerComb[i] == 1) {
      numLiters += containers[i];
    }
  }
  return numLiters;
}