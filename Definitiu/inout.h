#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>

using namespace std;

#define INPUT_FILE "d_pet_pictures.txt"
#define OUTPUT_FILE "a_out.txt"

map<string, int> tags;
vector<pair<int, vector<int> > > vertical_photos;
vector<pair<pair<int, int>, vector<int> > > horizontal_photos;
vector<vector<int> > all_photos;
vector<int> relate;
int M;

int obtain_num(const string& s) {
    map<string, int>::iterator it = tags.find(s);
    if (it != tags.end()) return it->second;
    else {
        tags.insert(make_pair(s, tags.size()));
        return tags[s];
    }
}

int count_distinct(const vector<int>& v1, const vector<int>& v2) {
    int i = 0;
    int j = 0;
    int sz1 = v1.size();
    int sz2 = v2.size();
    int inter = 0;
    while (i < sz1 and j < sz2) {
        if (i == j) {
            inter++;
            i++;
            j++;
        } 
        else if (i < j) i++;
        else j++;
    }
    return sz1 + sz2 - inter;
}

vector<int> unite(const vector<int>& v1, const vector<int>& v2) {
    int sz1 = v1.size();
    int sz2 = v2.size();
    vector<int> res;
    int i, j;
    i = j = 0;
    while (i < sz1 and j < sz2) {
        int sz3 = res.size();
        if (v1[i] == v2[j]) {
            res.push_back(v1[i]);
            i++;
            j++;
        }
        else if (v1[i] < v2[j]) {
            if (sz3 == 0 or res[sz3-1] != v1[i]) res.push_back(v1[i]);
            i++;
        }
        else {
            if (sz3 == 0 or res[sz3-1] != v2[j]) res.push_back(v2[j]);
            j++;
        }
    }
    
    while (i < sz1) {
        int sz3 = res.size();
        if (sz3 == 0 or res[sz3-1] != v1[i]) res.push_back(v1[i]);
        i++;    
    }
    while (j < sz2) {
        int sz3 = res.size();
        if (sz3 == 0 or res[sz3-1] != v2[j]) res.push_back(v2[j]);
        j++;
    }
    return res;
}

void fusion() {
    int sz = vertical_photos.size();
    vector<int> used(sz, false);
    for (int i = 0; i < sz; i++) {
        if (not used[i]) {
            int maxim = 0;
            int maxindex = 0;
            for (int j = 0; j < sz; j++) {
                if (not used[j] and j != i) {
                    int score = count_distinct(vertical_photos[i].second, vertical_photos[j].second);
                    if (score > maxim) {
                        maxim = score;
                        maxindex = j; 
                    }
                }
            }
            used[i] = used[maxindex] = true;
            horizontal_photos.push_back(make_pair(make_pair(relate[i], relate[maxindex]), unite(vertical_photos[i].second, vertical_photos[maxindex].second)));
        }
    }
}

void read_from_file() {
    ifstream inFile(INPUT_FILE);
    inFile >> M;
    all_photos = vector<vector<int> >(M);
    relate = vector<int>();
    for (int i = 0; i < M; i++) {
        char c;
        inFile >> c;
        int k;
        inFile >> k;
        for (int j = 0; j < k; j++) {
            string s;
            inFile >> s;
            all_photos[i].push_back(obtain_num(s));
        }
        sort(all_photos[i].begin(), all_photos[i].end());
        if (c == 'H') horizontal_photos.push_back(make_pair(make_pair(i, -1), all_photos[i]));
        else {
            relate.push_back(i);
            vertical_photos.push_back(make_pair(i, all_photos[i]));
        }
    }
    fusion();
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
