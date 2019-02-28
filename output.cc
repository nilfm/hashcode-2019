#include <fstream>
#include <iostream>
using namespace std;

const string PATH = "output.txt";

void write_to_file(const vector<vector<int> >& sol) {
    ofstream fileOut(PATH);
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
