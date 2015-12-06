/* Written for the C++14 compiler at "https://ideone.com/" */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>

using namespace std;

/* Prototypes */
int checkForDoubleLetter(string);
int countVowels(string);

int main() {
  string inputLine;
  //ifstream myfile ("Day5_input");

  int nice = 0;

  vector<regex> badStrings;
  badStrings.push_back(regex("^(.*)(ab)(.*)$"));
  badStrings.push_back(regex("^(.*)(cd)(.*)$"));
  badStrings.push_back(regex("^(.*)(pq)(.*)$"));
  badStrings.push_back(regex("^(.*)(xy)(.*)$"));

  //while(getline(myfile, inputLine)) {
  while(getline(cin, inputLine)) {
    int badStringFlag = 0;
    // Check for bad strings first
    for(vector<regex>::iterator it = badStrings.begin(); it != badStrings.end(); ++it) {
      regex badString = *it;
      if(regex_match(inputLine, badString)) {
        badStringFlag = 1;
        break;
      }
    }
    if((badStringFlag == 0) && (checkForDoubleLetter(inputLine) == 1) && (countVowels(inputLine) >= 3)) {
      ++nice;
    }
  }
  cout << nice << endl;

  //myfile.close();
  return 0;
}

int checkForDoubleLetter(string inputString) {
  int doubleLetterFlag = 0;
  string::size_type inputStringSize = inputString.size();
  for(string::size_type i = 0; i < (inputStringSize-1); ++i) {
    char currLetter = inputString[i];
    char nextLetter = inputString[i+1];
    if(currLetter == nextLetter) {
      doubleLetterFlag = 1;
      break;
    }
  }

  return doubleLetterFlag;
}

int countVowels(string inputString) {
  int numVowels = 0;
  string::size_type inputStringSize = inputString.size();
  for(string::size_type i = 0; i < inputStringSize; ++i) {
    char letter = inputString[i];
    switch(letter) {
      case 'a':
        ++numVowels;
        break;
      case 'e':
        ++numVowels;
        break;
      case 'i':
        ++numVowels;
        break;
      case 'o':
        ++numVowels;
        break;
      case 'u':
        ++numVowels;
        break;
      default:
        break;
    }
  }

  return numVowels;
}