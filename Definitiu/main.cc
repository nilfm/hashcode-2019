#include <cmath>
#include <algorithm>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

#include "inout.h"
using namespace std;

#define INPUT_FILE "???"
#define OUTPUT_FILE "???"

const int NUM_ITERS = 100;

typedef long long ll;

void calculate(ll& score, vector<vector<int> >& out) {

}

int main() {
    srand(time(0));
    read_from_file(INPUT_FILE, rides);
    int high_score = 0; //highscore inicial
    string enter;
    cout << "Press enter" << endl;
    ll iter = 0;
    while (iter%NUM_ITERS != 0 or getline(cin, enter)) {
        ll score;
        //TODO: crear out
        calculate(score, out);
        cout << "Finished iteration with " << score << " points" << endl;
        if (score > high_score) {
            cout << "Updating output file..." << endl;
            write_to_file(OUTPUT_FILE, out);
            cout << "Output file updated" << endl;
            high_score = score;
        }
        iter++;
        if (iter%NUM_ITERS == 0) cout << "Press enter" << endl;
    } 
}
