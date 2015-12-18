#include <string>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

/* Classes */
class Ingredient {
public:
  string name;
  int capacity;
  int durability;
  int flavor;
  int texture;
  int calories;

  Ingredient(const string& n, const int& cap, const int& d, const int& f, const int& t, const int& cal) : name(n), capacity(cap), durability(d), flavor(f), texture(t), calories(cal) {}
  Ingredient() {}
};

/* Prototypes */
void printCookie(int*);
int getCookieScore(int*, Ingredient*);
int getCookieCalories(int*, Ingredient*);

int main() {
  int cookie[4]; // The cookie combination. all 0s = all (first) ingredient. Etc.
  int score = -1;
  Ingredient ingredients[4]; // 4 ingredients max
  char nameTmp[20];
  int capacity, durability, flavor, texture, calories, i;

  FILE* fp = fopen("Day15_input", "r");
  i = 0;
  while(fscanf(fp, "%s capacity %d, durability %d, flavor %d, texture %d, calories %d", nameTmp, &capacity, &durability, &flavor, &texture, &calories) != EOF) {
    string name = nameTmp;
    // Remove colon from name
    name.erase(name.size() - 1);
    Ingredient tmp(name, capacity, durability, flavor, texture, calories);
    ingredients[i] = tmp;
    ++i;
  }
  fclose(fp);

  for(int a = 0; a < 101; ++a) {
    for(int b = 0; b < 101; ++b) {
      for(int c = 0; c < 101; ++c) {
        for(int d = 0; d < 101; ++d) {
          int sum = a+b+c+d;
          if(sum != 100) {
            continue;
          }
          cookie[0] = a;
          cookie[1] = b;
          cookie[2] = c;
          cookie[3] = d;
          int calories = getCookieCalories(cookie, ingredients);
          if(calories != 500) {
            continue;
          }
          int cookieScore = getCookieScore(cookie, ingredients);
          //printCookie(cookie);
          if(cookieScore > score) {
            score = cookieScore;
          }
        }
      }
    }
  }

  cout << score << endl;
  return 0;
}

void printCookie(int* cookie) {
  cout << "Cookie: ";
  for(int i = 0; i < 4; ++i) {
    cout << cookie[i] << " ";
  }
  cout << endl;
  return;
}

int getCookieScore(int* cookie, Ingredient* ingredients) {
  int capacity = 0;
  int durability = 0;
  int flavor = 0;
  int texture = 0;

  for(int i = 0; i < 4; ++i) {
    capacity += ingredients[i].capacity * cookie[i];
    durability += ingredients[i].durability * cookie[i];
    flavor += ingredients[i].flavor * cookie[i];
    texture += ingredients[i].texture * cookie[i];
  }

  if(capacity < 0) {
    capacity = 0;
  }
  if(durability < 0) {
    durability = 0;
  }
  if(flavor < 0) {
    flavor = 0;
  }
  if(texture < 0) {
    texture = 0;
  }

  return capacity * durability * flavor * texture;
}

int getCookieCalories(int* cookie, Ingredient* ingredients) {
  int calories = 0;
  for(int i = 0; i < 4; ++i) {
    calories += ingredients[i].calories * cookie[i];
  }
  return calories;
}