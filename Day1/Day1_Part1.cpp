/* Written for the C++14 compiler at "https://ideone.com/" */

#include <iostream>
#include <string>

using namespace std;

int main() {
  string input;
  getline(cin, input);
  int floor = 0;
  for(char& c : input) {
    if(c == '(') {
	  ++floor;
	}
	if(c == ')') {
	  --floor;
	}
  }
  
  cout << "Floor: " << floor << endl;
  
  return 0;
}