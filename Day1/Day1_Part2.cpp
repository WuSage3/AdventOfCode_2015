/* Written for the C++14 compiler at "https://ideone.com/" */

#include <iostream>
#include <string>

using namespace std;

int main() {
  string input;
  getline(cin, input);
  int floor = 0;
  int position = 1;
  int positionFoundFlag = 0;
  for(char& c : input) {
    if(c == '(') {
      ++floor;
      if(positionFoundFlag == 0) {
        if (floor == -1) {
          positionFoundFlag = 1;
        } else {
          ++position;
        }
      }
    }
    if(c == ')') {
      --floor;
      if(positionFoundFlag == 0) {
        if (floor == -1) {
          positionFoundFlag = 1;
        } else {
          ++position;
        }
      }
    }
  }

  cout << "Floor: " << floor << endl;
  cout << "First basement position: " << position << endl;

  return 0;
}