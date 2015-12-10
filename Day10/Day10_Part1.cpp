/* Written for the C++14 compiler at "https://ideone.com/" */

#include <string>
#include <sstream>
#include <iostream>

using namespace std;

// Solution from http://rosettacode.org/wiki/Look-and-say_sequence#C.2B.2B

/* Prototypes */
string lookandsay(const string&);

int main() {
  string input = "1113122113";

  cout << input << endl;
  for (int i = 0; i < 40; ++i) {
    input = lookandsay(input);
  }
  cout << input.size() << endl;
  return 0;
}

string lookandsay(const string& s) {
  ostringstream r;

  for (unsigned int i = 0; i != s.length();) {
    unsigned int new_i = s.find_first_not_of(s[i], i+1);
    if (new_i == string::npos) {
      new_i = s.length();
    }
    r << new_i - i << s[i];
    i = new_i;
  }
  return r.str();
}