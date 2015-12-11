/* Written for the C++14 compiler at "https://ideone.com/" */

#include <string>
#include <sstream>
#include <iostream>
using namespace std;

/* Prototypes */
int isGoodPW(const string&);
int firstRequirement(const string&);
int secondRequirement(const string&);
int thirdRequirement(const string&);
string iteratePassword(string, string::size_type);

int main() {
  string password = "vzbxkghb";

  do {
    password = iteratePassword(password, 7);
  } while(isGoodPW(password) != 1);

  // His PW expired again! Part 2:
  do {
    password = iteratePassword(password, 7);
  } while(isGoodPW(password) != 1);

  cout << password << endl;
  return 0;
}

int isGoodPW(const string& password) {
  int firstRequirementFlag = firstRequirement(password);
  int secondRequirementFlag = secondRequirement(password);
  int thirdRequirementFlag = thirdRequirement(password);

  if((firstRequirementFlag == 1) && (secondRequirementFlag == 1) && (thirdRequirementFlag == 1)) {
    return 1;
  }
  return 0;
}

int firstRequirement(const string& password) {
  for(string::size_type i = 0; i < 6; ++i) {
    char firstLetter = password[i];
    char secondLetter = password[i+1];
    char thirdLetter = password[i+2];

    if((secondLetter == firstLetter + 1) && (thirdLetter == secondLetter + 1)) {
      return 1;
    }
  }
  return 0;
}

int secondRequirement(const string& password) {
  for(string::size_type i = 0; i < 8; ++i) {
    char currLetter = password[i];
    switch(currLetter) {
      case 'i':
        return 0;
      case 'o':
        return 0;
      case 'l':
        return 0;
      default:
        break;
    }
  }
  return 1;
}

int thirdRequirement(const string& password) {
  for(string::size_type i = 0; i < 5; ++i) {
    char firstLetter = password[i];
    char secondLetter = password[i+1];
    if(firstLetter == secondLetter) {
      for(string::size_type j = i+2; j < 7; ++j) {
        char nextPairFirstLetter = password[j];
        char nextPairSecondLetter = password[j+1];
        if((nextPairFirstLetter == nextPairSecondLetter) && (nextPairFirstLetter != firstLetter)) {
          return 1;
        }
      }
      // If we get to this point, no double pair has been found. Safe to return.
      return 0;
    }
  }
}

string iteratePassword(string password, string::size_type currIndex) {
  if(currIndex < 0) {
    return password;
  }

  char currLetter = password[currIndex];
  switch(currLetter) {
    case 'z':
      password[currIndex] = 'a';
      password = iteratePassword(password, currIndex-1);
      break;
    default:
      password[currIndex] = currLetter + 1;
      break;
  }
  return password;
}

