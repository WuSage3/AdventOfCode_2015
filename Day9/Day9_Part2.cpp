/* Written for the C++14 compiler at "https://ideone.com/" */

#include <iostream>
#include <fstream>
#include <limits.h>

using namespace std;

/* Prototypes */
int tsp(int, int);

int dist[20][20]; // Assume 20x20 at most

// Solution taken from (I cheated, don't feel like doing the Traveling Salesperson Problem): https://www.reddit.com/r/adventofcode/comments/3w192e/day_9_solutions/cxsiu1p

int main() {
    int a, b, c;
    while (scanf("%d to %d = %d ", &a, &b, &c) != EOF) {
        dist[a][b] = c;
        dist[b][a] = c;
    }

    int ans = INT_MIN;
    for (int i = 0; i <= 7; i++) {
        ans = max(ans, tsp(i, (1<<i)));
    }

    printf("%d", ans);
    return 0;
}

int tsp(int pos, int used) {
    if (used == ((1<<8) - 1)) return 0;

    int ans = INT_MIN;
    for (int i = 0; i <= 7; i++) {
        if ((used & (1<<i)) == 0) {
            ans = max(ans, tsp(i, used | (1<<i)) + dist[pos][i]);
        }
    }
    return ans;
}
