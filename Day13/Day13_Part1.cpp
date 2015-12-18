/* Written for the C++14 compiler at "https://ideone.com/" */

#include <string>
#include <iostream>
#include <map>
#include <limits.h>
#include <vector>

using namespace std;

/* Prototypes */
void printHappinessTable(map<string, map<string, int>>*);
vector<string> getNamesFromHappinessTable(map<string, map<string, int>>*);
vector<string> getRemainingNames(const vector<string>&, const string&);
int getSeatingComboHappiness(map<string, map<string, int>>*, const vector<string>&);
string::size_type getLeftNeighborIndex(const string::size_type&, const string::size_type&);
string::size_type getRightNeighborIndex(const string::size_type&, const string::size_type&);

int main() {
  char currPersonTmp[8], gain_loseTmp[5], nextToPersonTmp[8];
  string currPerson, gain_lose, nextToPerson;
  int value;
  map<string, map<string, int>> happinessTable;
  int happiness = INT_MIN;
  vector<string> names;

  while(scanf("%s would %s %d happiness units by sitting next to %s.", currPersonTmp, gain_loseTmp, &value, nextToPersonTmp) != EOF) {
    currPerson = currPersonTmp;
    gain_lose = gain_loseTmp;
    nextToPerson = nextToPersonTmp;
    // Period keeps getting added to the nextToPerson, going to remove it
    nextToPerson.erase(nextToPerson.size()-1);
    if(gain_lose == "lose") {
      value = -1*value;
    }
    //cout << currPerson << " " << gain_lose << " " << value << " " << nextToPerson << endl;
    happinessTable[currPerson][nextToPerson] = value;
  }

  names = getNamesFromHappinessTable(&happinessTable);

  for(string seat1 : names) {
    vector<string> namesM1 = getRemainingNames(names, seat1);
    for(string seat2 : namesM1) {
      vector<string> namesM2 = getRemainingNames(namesM1, seat2);
      for(string seat3 : namesM2) {
        vector<string> namesM3 = getRemainingNames(namesM2, seat3);
        for(string seat4 : namesM3) {
          vector<string> namesM4 = getRemainingNames(namesM3, seat4);
          for(string seat5 : namesM4) {
            vector<string> namesM5 = getRemainingNames(namesM4, seat5);
            for(string seat6 : namesM5) {
              vector<string> namesM6 = getRemainingNames(namesM5, seat6);
              for(string seat7 : namesM6) {
                vector<string> namesM7 = getRemainingNames(namesM6, seat7);
                for(string seat8 : namesM7) {
                  vector<string> combo;
                  combo.push_back(seat1);
                  combo.push_back(seat2);
                  combo.push_back(seat3);
                  combo.push_back(seat4);
                  combo.push_back(seat5);
                  combo.push_back(seat6);
                  combo.push_back(seat7);
                  combo.push_back(seat8);
                  int totalComboHappiness = getSeatingComboHappiness(&happinessTable, combo);
                  if(totalComboHappiness > happiness) {
                    happiness = totalComboHappiness;
                  }
                  //string combination = seat1 + " " + seat2 + " " + seat3 + " " + seat4 + " " + seat5 + " " + seat6 + " " + seat7 + " " + seat8;
                  //cout << combination << endl;
                }
              }
            }
          }
        }
      }
    }
  }

  cout << "Total happiness: " << happiness << endl;
  //printHappinessTable(&happinessTable);

  return 0;
}

void printHappinessTable(map<string, map<string, int>>* happinessTablePointer) {
  for(map<string, map<string, int>>::iterator iter = (*(happinessTablePointer)).begin(); iter != (*(happinessTablePointer)).end(); ++iter) {
    string rater = iter->first;
    map<string, int> raterTable = iter->second;
    cout << rater << ": " << endl;
    for(map<string, int>::iterator tableIter = raterTable.begin(); tableIter != raterTable.end(); ++tableIter) {
      string ratee = tableIter->first;
      int value = tableIter->second;
      cout << "  " << ratee << ": " << value << endl;
    }
  }
}

vector<string> getNamesFromHappinessTable(map<string, map<string, int>>* happinessTablePointer) {
  vector<string> names;
  for(map<string, map<string, int>>::iterator iter = (*(happinessTablePointer)).begin(); iter != (*(happinessTablePointer)).end(); ++iter) {
    string rater = iter->first;
    names.push_back(rater);
  }
  return names;
}

vector<string> getRemainingNames(const vector<string>& nameList, const string& nameToRemove) {
  vector<string> names;

  for(string name : nameList) {
    if(name != nameToRemove) {
      names.push_back(name);
    }
  }

  return names;
}

int getSeatingComboHappiness(map<string, map<string, int>>* happinessTablePointer, const vector<string>& combo) {
  int happiness = 0;
  string::size_type size = combo.size();
  for(vector<string>::size_type i = 0; i != size; ++i) {
    string person = combo[i];
    string leftNeighbor = combo[getLeftNeighborIndex(i, size)];
    string rightNeighbor = combo[getRightNeighborIndex(i, size)];
    happiness += (*(happinessTablePointer))[person][leftNeighbor];
    happiness += (*(happinessTablePointer))[person][rightNeighbor];
  }
  return happiness;
}

string::size_type getLeftNeighborIndex(const string::size_type& currIndex, const string::size_type& size) {
  if(currIndex == 0) {
    return size-1;
  }
  return currIndex-1;
}

string::size_type getRightNeighborIndex(const string::size_type& currIndex, const string::size_type& size) {
  if(currIndex == size-1) {
    return 0;
  }
  return currIndex+1;
}