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
int areWeDoneYet(map<string, int>*);
void printSignals(map<string, uint16_t>*);
uint16_t handleNumSignalOp(uint16_t, string, string, string, map<string, uint16_t>*);
uint16_t handleSignalSignalOp(string, string, string, string, map<string, uint16_t>*);

int main() {
  string inputLine;
  //ifstream myfile ("Day7_input");

  vector<string> input;

  vector<vector<string>> parsedInput; // Contains LHS and RHS for each line

  map<string, uint16_t> signals;
  map<string, int> signalsDefined;

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

    signalsDefined[rightHandSide] = -1;
  }

  // Second, third, etc. passes.
  // Basically, go through the input each time, and add any constants or expressions that can now be reduced to constants
  while(areWeDoneYet(&signalsDefined) != 1) {
    for(vector<vector<string>>::iterator i = parsedInput.begin(); i != parsedInput.end(); ++i) {
      vector<string> parsedInputVector = *i;
      string leftHandSide = parsedInputVector.at(0);
      string rightHandSide = parsedInputVector.at(1);
      //cout << "LHS: \"" << leftHandSide << "\" RHS: \"" << rightHandSide << "\"" << endl;


      vector<string> LHS_parsed = split(leftHandSide, ' ');
      int LHS_size = LHS_parsed.size();
      string firstElement = LHS_parsed.at(0);
      int firstElemDigitFlag = isdigit(firstElement[0]);

      if(LHS_size == 1) { // We have an input which is "NUM -> signal" or "signal -> signal"
        if(firstElemDigitFlag != 0  && signalsDefined[rightHandSide] < 0) { // "NUM -> signal"
          uint16_t value = (uint16_t)atoi(firstElement.c_str());
          //cout << "Signal: " << rightHandSide << " Value: " << value << endl;
          signals[rightHandSide] = value;
          signalsDefined[rightHandSide] = 1;
        } else { // "signal -> signal"
          if(signalsDefined[firstElement] >= 0 && signalsDefined[rightHandSide] < 0) {
            signals[rightHandSide] = signals[firstElement];
            signalsDefined[rightHandSide] = 1;
          }
        }
      } else {
        if(firstElement == "NOT") { // We have an input which is "NOT signal -> signal"
          string secondElement = LHS_parsed.at(1);
          //cout << "NOT " << secondElement << endl;
          if(signalsDefined[secondElement] >= 0 && signalsDefined[rightHandSide] < 0) {
            signals[rightHandSide] = ~signals[secondElement];
            signalsDefined[rightHandSide] = 1;
          }
        } else { // 3-element LHS
          string op = LHS_parsed.at(1);
          string thirdElement = LHS_parsed.at(2);
          int thirdElemDigitFlag = isdigit(thirdElement[0]);
          if(firstElemDigitFlag != 0) { // "NUM OP signal -> signal" - Assume we have only one "raw number" element per line
            uint16_t value = (uint16_t)atoi(firstElement.c_str());
            if(signalsDefined[thirdElement] >= 0 && signalsDefined[rightHandSide] < 0) {
              signals[rightHandSide] = handleNumSignalOp(value, thirdElement, rightHandSide, op, &signals);
              signalsDefined[rightHandSide] = 1;
            }
          } else if(thirdElemDigitFlag != 0) { // "signal OP NUM -> signal" - Assume we have only one "raw number" element per line
            uint16_t value = (uint16_t)atoi(thirdElement.c_str());
            if(signalsDefined[firstElement] >= 0 && signalsDefined[rightHandSide] < 0) {
              signals[rightHandSide] = handleNumSignalOp(value, firstElement, rightHandSide, op, &signals);
              signalsDefined[rightHandSide] = 1;
            }
          } else { // "Signal OP Signal -> signal"
            if((signalsDefined[firstElement] >= 0) && (signalsDefined[thirdElement] >= 0) && signalsDefined[rightHandSide] < 0) {
              signals[rightHandSide] = handleSignalSignalOp(firstElement, thirdElement, rightHandSide, op, &signals);
              signalsDefined[rightHandSide] = 1;
            }
          }
        }
      }
    }
  }

  // Part 2:
  // Short wire a to wire b
  signals["b"] = signals["a"];

  // Reset everything but wire "b"
  for(map<string, uint16_t>::iterator iter = signals.begin(); iter != signals.end(); ++iter) {
    string signal = iter->first;
    if(signal != "b") {
      signalsDefined[signal] = -1;
    }
  }

  // Run the same loop again, but with only wire b defined
  while(areWeDoneYet(&signalsDefined) != 1) {
    for(vector<vector<string>>::iterator i = parsedInput.begin(); i != parsedInput.end(); ++i) {
      vector<string> parsedInputVector = *i;
      string leftHandSide = parsedInputVector.at(0);
      string rightHandSide = parsedInputVector.at(1);
      //cout << "LHS: \"" << leftHandSide << "\" RHS: \"" << rightHandSide << "\"" << endl;


      vector<string> LHS_parsed = split(leftHandSide, ' ');
      int LHS_size = LHS_parsed.size();
      string firstElement = LHS_parsed.at(0);
      int firstElemDigitFlag = isdigit(firstElement[0]);

      if(LHS_size == 1) { // We have an input which is "NUM -> signal" or "signal -> signal"
        if(firstElemDigitFlag != 0  && signalsDefined[rightHandSide] < 0) { // "NUM -> signal"
          uint16_t value = (uint16_t)atoi(firstElement.c_str());
          //cout << "Signal: " << rightHandSide << " Value: " << value << endl;
          signals[rightHandSide] = value;
          signalsDefined[rightHandSide] = 1;
        } else { // "signal -> signal"
          if(signalsDefined[firstElement] >= 0 && signalsDefined[rightHandSide] < 0) {
            signals[rightHandSide] = signals[firstElement];
            signalsDefined[rightHandSide] = 1;
          }
        }
      } else {
        if(firstElement == "NOT") { // We have an input which is "NOT signal -> signal"
          string secondElement = LHS_parsed.at(1);
          //cout << "NOT " << secondElement << endl;
          if(signalsDefined[secondElement] >= 0 && signalsDefined[rightHandSide] < 0) {
            signals[rightHandSide] = ~signals[secondElement];
            signalsDefined[rightHandSide] = 1;
          }
        } else { // 3-element LHS
          string op = LHS_parsed.at(1);
          string thirdElement = LHS_parsed.at(2);
          int thirdElemDigitFlag = isdigit(thirdElement[0]);
          if(firstElemDigitFlag != 0) { // "NUM OP signal -> signal" - Assume we have only one "raw number" element per line
            uint16_t value = (uint16_t)atoi(firstElement.c_str());
            if(signalsDefined[thirdElement] >= 0 && signalsDefined[rightHandSide] < 0) {
              signals[rightHandSide] = handleNumSignalOp(value, thirdElement, rightHandSide, op, &signals);
              signalsDefined[rightHandSide] = 1;
            }
          } else if(thirdElemDigitFlag != 0) { // "signal OP NUM -> signal" - Assume we have only one "raw number" element per line
            uint16_t value = (uint16_t)atoi(thirdElement.c_str());
            if(signalsDefined[firstElement] >= 0 && signalsDefined[rightHandSide] < 0) {
              signals[rightHandSide] = handleNumSignalOp(value, firstElement, rightHandSide, op, &signals);
              signalsDefined[rightHandSide] = 1;
            }
          } else { // "Signal OP Signal -> signal"
            if((signalsDefined[firstElement] >= 0) && (signalsDefined[thirdElement] >= 0) && signalsDefined[rightHandSide] < 0) {
              signals[rightHandSide] = handleSignalSignalOp(firstElement, thirdElement, rightHandSide, op, &signals);
              signalsDefined[rightHandSide] = 1;
            }
          }
        }
      }
    }
  }

  cout << endl << "Signals: " << endl;
  printSignals(&signals);

  //myfile.close();
  return 0;
}

uint16_t handleNumSignalOp(uint16_t value, string LHS_signal, string RHS_signal, string op, map<string, uint16_t>* signalsPointer) {
  uint16_t returnVal;

  if(op == "AND") {
    returnVal = (*(signalsPointer))[LHS_signal] & value;
  } else if(op == "OR") {
    returnVal = (*(signalsPointer))[LHS_signal] | value;
  } else if(op == "LSHIFT") {
    returnVal = (*(signalsPointer))[LHS_signal] << value;
  } else if(op == "RSHIFT") {
    returnVal = (*(signalsPointer))[LHS_signal] >> value;
  }

  return returnVal;
}

uint16_t handleSignalSignalOp(string LHS_signal1, string LHS_signal2, string RHS_signal, string op, map<string, uint16_t>* signalsPointer) {
  uint16_t returnVal = handleNumSignalOp((*(signalsPointer))[LHS_signal1], LHS_signal2, RHS_signal, op, signalsPointer);
  return returnVal;
}

void printSignals(map<string, uint16_t>* signalsPointer) {
  for(map<string, uint16_t>::iterator iter = (*(signalsPointer)).begin(); iter != (*(signalsPointer)).end(); ++iter) {
    string signal = iter->first;
    uint16_t signalValue = iter->second;
    if(signalValue > -1) {
      cout << " Signal: " << signal << " Value: " << signalValue << endl;
    }
  }
  return;
}

int areWeDoneYet(map<string, int>* signalsDefinedPointer) {
  int flag = 1;
  for(map<string, int>::iterator iter = (*(signalsDefinedPointer)).begin(); iter != (*(signalsDefinedPointer)).end(); ++iter) {
    int signalValue = iter->second;
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