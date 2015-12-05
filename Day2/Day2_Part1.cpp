/* Written for the C++14 compiler at "https://ideone.com/" */

#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

/* Prototypes */
vector<string>& split(const string&, char, vector<string>&);
vector<string>  split(const string&, char);
int getSurfaceArea(int, int, int);
int getSmallestSideArea(int, int, int);

int main() {
  string input;
  vector<string> parsedInput;
  int l, w, h, surfaceArea, smallestSideArea;
  int totalWrappingPaper = 0;
  while(getline(cin, input)) {
    parsedInput = split(input, 'x');
    l = stoi(parsedInput.at(0));
    w = stoi(parsedInput.at(1));
    h = stoi(parsedInput.at(2));
    // cout << "Input: " << input << " L W H: " << l << " " << w << " " << h << endl;
    surfaceArea = getSurfaceArea(l, w, h);
    smallestSideArea = getSmallestSideArea(l, w, h);
    totalWrappingPaper += surfaceArea + smallestSideArea;
  }

  cout << "Total wrapping paper: " << totalWrappingPaper << " feet." << endl;
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

int getSurfaceArea(int l, int w, int h) {
  int surfaceArea = 2*l*w + 2*w*h + 2*h*l;
  return surfaceArea;
}

int getSmallestSideArea(int l, int w, int h) {
  int side1 = l*w;
  int side2 = w*h;
  int side3 = h*l;

  int smallestSideArea = side1;

  if(side2 < smallestSideArea) {
    smallestSideArea = side2;
  }
  if(side3 < smallestSideArea) {
    smallestSideArea = side3;
  }

  return smallestSideArea;
}
