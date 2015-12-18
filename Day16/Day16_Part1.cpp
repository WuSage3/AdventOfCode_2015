/* Written for the C++14 compiler at "https://ideone.com/" */

#include <string>
#include <iostream>
#include <sstream>
#include <map>
#include <vector>

using namespace std;

/* Classes */
class Sue {
public:
  int number;
  map<string, int> things;

  Sue() {}
  Sue(const int& n, const string& thing1, const string& thing2, const string& thing3, const int& thing1Val, const int& thing2Val, const int& thing3Val) : number(n) {
    things[thing1] = thing1Val;
    things[thing2] = thing2Val;
    things[thing3] = thing3Val;
  }
};

class MysterySue {
public:
  map<string, int> things;

  MysterySue() {
    things["children"] = 3;
    things["cats"] = 7;
    things["samoyeds"] = 2;
    things["pomeranians"] = 3;
    things["akitas"] = 0;
    things["vizslas"] = 0;
    things["goldfish"] = 5;
    things["trees"] = 3;
    things["cars"] = 2;
    things["perfumes"] = 1;
  }
};

/* Prototypes */
vector<string>& split(const string&, char, vector<string>&);
vector<string> split(const string&, char);
int sueMatches(Sue*, MysterySue*);

int main() {
  string thing1, thing2, thing3, inputLine;
  int thing1Val, thing2Val, thing3Val, sueNumber;
  MysterySue mysterySue;
  Sue currSue;


  while(getline(cin, inputLine)) {
    vector<string> lineSplit = split(inputLine, ' ');
    sueNumber = atoi(lineSplit.at(1).c_str());
    thing1 = lineSplit.at(2);
    thing1Val = atoi(lineSplit.at(3).c_str());
    thing2 = lineSplit.at(4);
    thing2Val = atoi(lineSplit.at(5).c_str());
    thing3 = lineSplit.at(6);
    thing3Val = atoi(lineSplit.at(7).c_str());
    //cout << sueNumber << " " << thing1 << " " << thing1Val << " " << thing2 << " " << thing2Val << " " << thing3 << " " << thing3Val << endl;
    Sue newSue(sueNumber, thing1, thing2, thing3, thing1Val, thing2Val, thing3Val);
    currSue = newSue;
    if(sueMatches(&currSue, &mysterySue) == 1) {
      break;
    }
  }

  cout << currSue.number << endl;
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

int sueMatches(Sue* currSue, MysterySue* mysterySue) {
  int returnFlag = 1;
  for(map<string, int>::iterator iter = (*currSue).things.begin(); iter != (*currSue).things.end(); ++iter) {
    string thing = iter->first;
    int value = iter->second;
    if((*mysterySue).things[thing] != value) {
      returnFlag = 0;
      break;
    }
  }
  return returnFlag;
}