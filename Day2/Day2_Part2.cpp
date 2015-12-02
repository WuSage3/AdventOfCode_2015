/* Written for the C++14 compiler at "https://ideone.com/" */

#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

/* Prototypes */
vector<string>& split(const string&, char, vector<string>&);
vector<string>  split(const string&, char);
int getVolume(int, int, int);
int getSmallestSidePerimeter(int, int, int);

int main() {
  string input;
  vector<string> parsedInput;
  int l, w, h, volume, smallestSidePerimeter;
  int totalRibbon = 0;
  while(getline(cin, input)) {
    parsedInput = split(input, 'x');
	l = stoi(parsedInput.at(0));
	w = stoi(parsedInput.at(1));
	h = stoi(parsedInput.at(2));
	// cout << "Input: " << input << " L W H: " << l << " " << w << " " << h << endl;
	volume = getVolume(l, w, h);
	smallestSidePerimeter = getSmallestSidePerimeter(l, w, h);
	totalRibbon += volume + smallestSidePerimeter;
  }
  
  cout << "Total ribbon: " << totalRibbon << " feet." << endl;
  return 0;
}

vector<string>& split(const string& s, char delim, vector<string>& elems) {
	/* Taken from: "http://stackoverflow.com/questions/236129/split-a-string-in-c"
	 * Stores results in pre-constructed vector
	 */
    stringstream ss(s);
    string item;
    while (getline(ss, item, delim)) {
      elems.push_back(item);
    }
    return elems;
}

vector<string> split(const string& s, char delim) {
	/* Taken from: "http://stackoverflow.com/questions/236129/split-a-string-in-c"
	 * Returns a new vector
	 */
    vector<string> elems;
    split(s, delim, elems);
    return elems;
}

int getVolume(int l, int w, int h) {
  int volume = l*w*h;
  return volume;
}

int getSmallestSidePerimeter(int l, int w, int h) {
  int side1 = l+l+w+w;
  int side2 = w+w+h+h;
  int side3 = h+h+l+l;
  
  int smallestSidePerimeter = side1;
  
  if(side2 < smallestSidePerimeter) {
    smallestSidePerimeter = side2;
  }
  if(side3 < smallestSidePerimeter) {
    smallestSidePerimeter = side3;
  }
  
  return smallestSidePerimeter;
}
