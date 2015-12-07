/* Written for the C++14 compiler at "https://ideone.com/" */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <map>

using namespace std;

/* Prototypes */
vector<string>& split(const string&, char, vector<string>&);
vector<string>  split(const string&, char);
int areWeDoneYet(map<string, int16_t>*);
void printSignals(map<string, int16_t>*);

int main() {
  int16_t TODO_TODO = -2;
  string inputLine;
  //ifstream myfile ("Day7_input");

  vector<string> input;

  vector<vector<string>> parsedInput; // Contains LHS and RHS for each line

  map<string, int16_t> signals;

  //while(getline(myfile, inputLine)) {
  while(getline(cin, inputLine)) {
    input.push_back(inputLine);
  }

  // First pass - define all the signals, initialize to -1, parse input
  for(vector<string>::iterator i = input.begin(); i != input.end(); ++i) {
    string inputLine = *i;
    vector<string> parsedInputLine = split(inputLine, '-');
    string leftHandSide = parsedInputLine.at(0);
    leftHandSide.erase(leftHandSide.size() - 1); // Delete last space from LHS
    string rightHandSide = split(parsedInputLine.at(1), '>').at(1);
    rightHandSide.erase(0, 1); // Delete first space from RHS
    //cout << "LHS: \"" << leftHandSide << "\" RHS: \"" << rightHandSide << "\"" << endl;

    vector<string> LHSRHS;
    LHSRHS.push_back(leftHandSide);
    LHSRHS.push_back(rightHandSide);
    parsedInput.push_back(LHSRHS);

    signals[rightHandSide] = -1;
  }

  // Second, third, etc. passes.
  // Basically, go through the input each time, and add any constants or expressions that can now be reduced to constants
  while(areWeDoneYet(&signals) != 1) {
    int currInstruction = 0;
    vector<int> circuitElementsToRemoveFromInput;
    for(vector<vector<string>>::iterator i = parsedInput.begin(); i != parsedInput.end(); ++i) {
      vector<string> parsedInput = *i;
      string leftHandSide = parsedInput.at(0);
      string rightHandSide = parsedInput.at(1);
      //cout << "LHS: \"" << leftHandSide << "\" RHS: \"" << rightHandSide << "\"" << endl;


      vector<string> LHS_parsed = split(leftHandSide, ' ');
      int LHS_size = LHS_parsed.size();
      string firstElement = LHS_parsed.at(0);

      /*
      if(LHS_size == 1) {
        cout << "LHS: " << leftHandSide << endl;
      }
      */

      if(isdigit(firstElement[0]) && LHS_size == 1) { // We have a signal which is "NUM -> signal"
        int16_t value = (int16_t)atoi(firstElement.c_str());
        //cout << "Signal: " << rightHandSide << " Value: " << value << endl;
        signals[rightHandSide] = value;
        circuitElementsToRemoveFromInput.push_back(currInstruction);
      } else {
        if(firstElement == "NOT") { // We have a signal which is "NOT signal -> signal"
          string secondElement = LHS_parsed.at(1);
          //cout << "NOT " << secondElement << endl;
          if(signals[secondElement] >= 0) {
            circuitElementsToRemoveFromInput.push_back(currInstruction);
            signals[rightHandSide] = ~signals[secondElement];
          } else {
            signals[rightHandSide] = TODO_TODO; // Change to -1 when everything is fleshed out
          }
        } else {
          signals[rightHandSide] = TODO_TODO;
        }
      }

      ++currInstruction;
    }

    // Remove instructions in parsedInput so we don't go over redundant ones
    for(vector<int>::iterator i = circuitElementsToRemoveFromInput.begin(); i != circuitElementsToRemoveFromInput.end(); ++i) {
      int index = *i;
      parsedInput.erase(parsedInput.begin() + index);
    }
  }

  cout << endl << "Signals: " << endl;
  printSignals(&signals);

  //myfile.close();
  return 0;
}

void printSignals(map<string, int16_t>* signalsPointer) {
  for(map<string, int16_t>::iterator iter = (*(signalsPointer)).begin(); iter != (*(signalsPointer)).end(); ++iter) {
    string signal = iter->first;
    int16_t signalValue = iter->second;
    if(signalValue >= 0) {
      cout << " Signal: " << signal << " Value: " << signalValue << endl;
    }
  }
  return;
}

int areWeDoneYet(map<string, int16_t>* signalsPointer) {
  int flag = 1;
  for(map<string, int16_t>::iterator iter = (*(signalsPointer)).begin(); iter != (*(signalsPointer)).end(); ++iter) {
    int16_t signalValue = iter->second;
    if(signalValue == -1) {
      flag = 0;
      break;
    }
  }

  return flag;
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