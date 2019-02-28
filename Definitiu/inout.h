#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>

using namespace std;

#define INPUT_FILE "a_example.txt"
#define OUTPUT_FILE "a_out.txt"

map<string, int> tags;
vector<pair<int, vector<int> > > vertical_photos;
vector<pair<int, vector<int> > > horizontal_photos;
vector<vector<int> > all_photos;
int M;

int obtain_num(const string& s) {
    map<string, int>::iterator it = tags.find(s);
    if (it != tags.end()) return it->second;
    else {
        tags.insert(make_pair(s, tags.size()));
        return tags[s];
    }
}

void read_from_file() {
    ifstream inFile(INPUT_FILE);
    inFile >> M;
    all_photos = vector<vector<int> >(M);
    for (int i = 0; i < M; i++) {
        char c;
        inFile >> c;
        int k;
        inFile >> k;
        for (int j = 0; j < k; j++) {
            string s;
            inFile >> s;
            all_photos[i][j] = obtain_num(s);
        }
        sort(all_photos[i].begin(), all_photos[i].end());
        if (c == 'H') horizontal_photos.push_back(make_pair(i, all_photos[i]));
        else vertical_photos.push_back(make_pair(i, all_photos[i]));
    }
}


void write_to_file(const vector<pair<int, int> >& sol) {
    ofstream fileOut(OUTPUT_FILE);
    int m = sol.size();
    fileOut << M << endl;
    for (int i = 0; i < m; i++) {
        fileOut << sol[i].first;
        if (sol[i].second != -1) fileOut << " " << sol[i].second << endl;
        else fileOut << endl;
    }
    cout << "Output file overwritten with solution" << endl;
}
