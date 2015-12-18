/* Written for the C++14 compiler at "https://ideone.com/" */

#include <string>
#include <iostream>
#include <limits.h>

using namespace std;

/* Prototypes */
int simulateReindeer(int, int, int, int);

int main() {
  char currReindeerTmp[8];
  string currReindeer;
  int numSeconds = 2503;
  int speed, time, restTime;
  int maxDist = INT_MIN;

  while(scanf("%s can fly %d km/s for %d seconds, but then must rest for %d seconds.", currReindeerTmp, &speed, &time, &restTime) != EOF) {
    currReindeer = currReindeerTmp;
    int dist = simulateReindeer(speed, time, restTime, numSeconds);
    if(dist > maxDist) {
      maxDist = dist;
    }
  }

  cout << maxDist << endl;
  return 0;
}

int simulateReindeer(int speed, int time, int restTime, int duration) {
  int currTime = 0;
  int currDist = 0;

  while(currTime < duration) {
    for(int i = 0; (i < time) && (currTime < duration); ++i) {
      currDist += speed;
      ++currTime;
    }
    for(int i = 0; (i < restTime) && (currTime < duration); ++i) {
      ++currTime;
    }
  }

  return currDist;
}