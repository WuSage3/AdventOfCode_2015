/* Written for the C++14 compiler at "https://ideone.com/" */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

/* Prototypes */
string getCodeRep(string);

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
    int stringMemorySize = myInputLine.size();
    string codeRepresentation;
    int stringCodeSize;
    totalMemorySize += stringMemorySize;


    codeRepresentation = getCodeRep(myInputLine);

    // Add beginning and ending quotes
    codeRepresentation = '"' + codeRepresentation + '"';

    stringCodeSize = codeRepresentation.size();
    totalCodeSize += stringCodeSize;

  }

  int difference = totalCodeSize - totalMemorySize;
  cout << "Code size minus memory size: " << difference << endl;

  //myfile.close();
  return 0;
}

string getCodeRep(string inputLine) {
  string codeRepresentation = "";

  // Iterate over each character
  string::size_type i = 0;
  while(i < inputLine.size()) {
    char currChar = inputLine[i];
    if(currChar == '"' || currChar == '\\') { // Have to escape the escape
      codeRepresentation += '\\';
    }
    codeRepresentation += currChar;
    ++i;
  }

  return codeRepresentation;
}