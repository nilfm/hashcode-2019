#include <cmath>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

int R, C, F, N, B, T;

int dist(int ri, int ci, int rf, int cf) {
    return abs(rf-ri) + abs(cf-ci);
}

struct Ride {
    int ri, ci, rf, cf, s, f, num, real_s, real_f; 
};

vector<Ride> rides;

void write_to_file(const vector<vector<int> >& sol) {
    ofstream fileOut("output.txt");
    int m = sol.size();
    for (int i = 0; i < m; i++) {
        int k = sol[i].size();
        fileOut << k;
        for (int j = 0; j < k; j++) {
            fileOut << " " << sol[i][j]; 
        }
        fileOut << endl;
    }
    cout << "Output file overwritten with solution" << endl;
}

void read_input() {
    ifstream inFile("a_example.in");
    inFile >> R >> C >> F >> N >> B >> T;
    rides = vector<Ride>(N);
    for (int i = 0; i < N; i++) {
        inFile >> rides[i].ri >> rides[i].ci >> rides[i].rf >> rides[i].cf >> rides[i].s >> rides[i].f;
        rides[i].num = i;
        rides[i].real_s = rides[i].real_f = -1;
    }
}

void calculate(int& score, vector<vector<int> >& out) {
    // TO DO
}

int main() {
    read_input();
    int high_score = 0; //highscore inicial
    string enter;
    cout << "Press enter" << endl;
    while (getline(cin, enter)) {
        int score;
        vector<vector<int> > out;
        calculate(score, out);
        cout << "Finished iteration with " << score << " points" << endl;
        if (score > high_score) {
            cout << "Updating output file..." << endl;
            write_to_file(out);
            cout << "Output file updated" << endl;
        }
        cout << "Press enter" << endl;
    } 
}
