/* Written for the C++14 compiler at "https://ideone.com/" */

#include <string>
#include <iostream>

using namespace std;

/* Classes */
class Reindeer {
public:
  int speed;
  int time;
  int restTime;
  string name;
  int counter = 0;
  int dist = 0;
  int numPoints = 0;

  Reindeer(const string& n, const int& s, const int& t, const int& r) : name(n), speed(s), time(t), restTime(r) {}
  Reindeer() {}

  void advanceDeer(void) {
    if(counter >= restTime + time) {
      counter = 0;
    }
    if(counter < time) {
        dist += speed;
    }
    counter += 1;
  }
};

int main() {
  char currReindeerTmp[8];
  string currReindeer;
  int numSeconds = 2503;
  int speed, time, restTime;
  Reindeer deerArray[9];

  int i = 0;
  while(scanf("%s can fly %d km/s for %d seconds, but then must rest for %d seconds.", currReindeerTmp, &speed, &time, &restTime) != EOF) {
    currReindeer = currReindeerTmp;
    Reindeer reindeerInit(currReindeer, speed, time, restTime);
    deerArray[i] = reindeerInit;
    ++i;
  }

  for(i = 0; i < numSeconds; ++i) {
    int currDeer;
    for(currDeer = 0; currDeer < 9; ++currDeer) {
      deerArray[currDeer].advanceDeer();
    }
    // Determine this second's winner
    int currWinner = 0;
    for(currDeer = 0; currDeer < 9; ++currDeer) {
      if(deerArray[currDeer].dist > deerArray[currWinner].dist) {
        currWinner = currDeer;
      }
    }
    // Distribute points
    int winningDist = deerArray[currWinner].dist;
    for(currDeer = 0; currDeer < 9; ++currDeer) {
      if(deerArray[currDeer].dist == winningDist) {
        deerArray[currDeer].numPoints += 1;
      }
    }
  }

  for(i = 0; i < 9; ++i) {
    cout << "Deer: " << deerArray[i].name << " Points: " << deerArray[i].numPoints << endl;
  }
  return 0;
}