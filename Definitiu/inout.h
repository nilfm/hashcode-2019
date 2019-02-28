
#include <string>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

void read_from_file(string path, ???)
{
    ifstream inFile(path);
    for (int i = 0; i < ??; i++) {
    }
}


void write_to_file(string path, const vector<vector<int> >& sol)
{
    ofstream fileOut(path);
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