/* Written for the C++14 compiler at "https://ideone.com/" */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

/* Prototypes */
string getMemoryRep(string);

int main() {
  string inputLine;
  vector<string> input;
  //ifstream myfile ("Day8_input");

  int totalCodeSize = 0;
  int totalMemorySize = 0;


  //while(getline(myfile, inputLine)) {
  while(getline(cin, inputLine)) {
    input.push_back(inputLine);
  }

  for(vector<string>::iterator i = input.begin(); i != input.end(); ++i) {
    string myInputLine = *i;
    int stringCodeSize = myInputLine.size();
    string memoryRepresentation;
    int stringMemorySize;
    totalCodeSize += stringCodeSize;
    //cout << "Code String: " << myInputLine << " Size: " << stringCodeSize << endl;

    // Remove first and last double-quotes
    myInputLine.erase(0, 1);
    myInputLine.erase(myInputLine.size() - 1);

    memoryRepresentation = getMemoryRep(myInputLine);

    stringMemorySize = memoryRepresentation.size();
    totalMemorySize += stringMemorySize;
    //cout << "  Memory String: " << memoryRepresentation << " Size: " << stringMemorySize << endl;

  }

  int difference = totalCodeSize - totalMemorySize;
  cout << "Code size minus memory size: " << difference << endl;

  //myfile.close();
  return 0;
}

string getMemoryRep(string inputLine) {
  string memoryRepresentation = "";

  char dummyChar = 'h';

  // Iterate over each character
  string::size_type i = 0;
  while(i < inputLine.size()) {
    char currChar = inputLine[i];
    if(currChar == '\\') { // Have to escape the escape. This is saying if currChar == a lone backslash
      char nextChar = inputLine[i+1];
      if(nextChar == '"' || nextChar == '\\') { // We have backslash-" or double-backslash
        memoryRepresentation += nextChar;
        i+=2; // Skip the next char, already added
      } else { // We have backslash-xNN where NN is a hexadecimal number
        // nextChar == x
        unsigned char hexNumAsChar; // Chars go from -128 to 127, need it 0 to 255
        char num1 = inputLine[i+2];
        char num2 = inputLine[i+3];
        string hexNum = "";
        hexNum += num1;
        hexNum += num2;
        hexNumAsChar = (unsigned char)strtol(hexNum.c_str(), 0, 16);
        // I can't actually add every character to the memory representation as some fall in the extended ascii table which ideone.com doesn't support.
        // So I will be adding a dummy character to fix this
        memoryRepresentation += dummyChar;
        // Skip the x and NN in \xnn.
        i+=4;
      }
    } else {
      memoryRepresentation += currChar;
      ++i;
    }
  }

  return memoryRepresentation;
}