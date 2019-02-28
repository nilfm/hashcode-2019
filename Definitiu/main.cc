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
    int sz = horizontal_photos.size();
    score = 0;
    out = vector<pair<int, int> >(sz, make_pair(-1, -1));
    for (int i = 0; i < (int)horizontal_photos.size(); i++) {
        if (i%1000 == 0) cerr << "i = " << i << endl;
        int id1 = horizontal_photos[i].first.first;
        int id2 = horizontal_photos[i].first.second;
        vector<int>& tags_vec = horizontal_photos[i].second;
        
        int posicio;
        if (i < sz/3) {
            do {
                posicio = rand()%sz;
            } while (out[posicio].first != -1);
            if (posicio < sz-1 and out[posicio+1].first != -1) {
                int index = (out[posicio+1].second == -1 ? posicio+1 : relate2[out[posicio+1].first]);
                score += interest(tags_vec, horizontal_photos[index].second);
            }
            if (posicio > 0 and out[posicio-1].first != -1) {
                int index = (out[posicio-1].second == -1 ? posicio-1 : relate2[out[posicio-1].first]);
                score += interest(tags_vec, horizontal_photos[index].second);
            }
        }
        else {
            int maxim = -1;
            int maxindex = 0;
            for (int j = 0; j < sz; j++) {
                if (out[j].first == -1) {
                    int curr = 0;
                    if (j < sz-1 and out[j+1].first != -1) {
                        int index = j+1;
                        if (out[j+1].second != -1) index = relate2[relateinv[out[j+1].first]];
                        curr += interest(tags_vec, horizontal_photos[index].second);
                    }
                    if (j > 0 and out[j-1].first != -1) {
                        int index = j-1;
                        if (out[j-1].second != -1) index = relate2[relateinv[out[j-1].first]];
                        curr += interest(tags_vec, horizontal_photos[index].second);
                    }
                    if (curr > maxim) {
                        maxim = curr;
                        maxindex = j;
                    }
                }
            }
            posicio = maxindex;
            score += maxim;
        }
        out[posicio] = make_pair(id1, id2);
    }
}

int main() {
    srand(time(0));
    read_from_file();
    cout << "File read and processed" << endl;
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
            write_to_file(out);
            cout << "Output file updated" << endl;
            high_score = score;
        }
        iter++;
        if (iter%NUM_ITERS == 0) cout << "Press enter" << endl;
    } 
}
