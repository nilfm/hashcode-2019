#include <cmath>
#include <algorithm>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

#include "inout.h"
using namespace std;

const int NUM_ITERS = 100;

typedef long long ll;

ll interest(vector<int>& v1, vector<int>& v2) {
    ll opt1 = 0; //interseccio
    ll opt2 = 0; //v1 menys v2
    ll opt3 = 0; //v2 menys v1
    int sz1 = v1.size();
    int sz2 = v2.size();
    int i = 0;
    int j = 0;
    while (i < sz1 and j < sz2) {
        if (v1[i] == v2[j]) {
            opt1++;
            i++;
            j++;
        }
        else if (v1[i] < v2[j]) {
            opt2++;
            i++;
        }
        else {
            opt3++;
            j++;
        }
    }
    while (i < sz1) {
        i++;
        opt2++;
    }
    while (j < sz2) {
        j++;
        opt3++;
    }
    return min(min(opt1, opt2), opt3);
}

void calculate(ll& score, vector<pair<int, int> >& out) {
    
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
        vector<pair<int, int> > out;
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
