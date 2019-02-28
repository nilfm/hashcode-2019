#include <cmath>
#include <algorithm>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <set>

#include "inout.h"
using namespace std;

const int NUM_ITERS = 100;

struct Slide
{
    int id1, id2;
    int interest;

    Slide()
    {
        interest = -1;
    }
};

typedef long long ll;

int best_pair(int pos, const vector<pair<int, vector<int> > >& vertical_photos, const vector<bool>& checked)
{
    int bestpos = -1;
    int best = 99;

    for(int i = 0; i < vertical_photos.size(); i++)
    {
        if(i != pos and not checked[i])
        {
            int n1 = vertical_photos[pos].second.size();
            int n2 = vertical_photos[i].second.size();

            set<int> u;

            for(int j = 0; j < n1; j++) u.insert(vertical_photos[pos].second[j]);
            for(int k = 0; k < n2; k++) u.insert(vertical_photos[i].second[k]);

            int diff = (n1+n2) - u.size();

            if(diff < best)
            {
                best = diff;
                bestpos = i;
            }
        }
    }

    return bestpos;
}

void find_pairs(const vector<pair<int, vector<int> > >& vertical_photos, vector<pair<int,int>>& vertical_pairs)
{
    vector<bool> checked(vertical_photos.size(), false);

    for(int i = 0; i < vertical_photos.size(); i++)
    {
        checked[i] = true;
        int best = best_pair(i, vertical_photos, checked);
        if(best != -1)
        {
            checked[best] = true;
            vertical_pairs.push_back(make_pair(i, best));
        }
    }
}

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
    return min(min(opt1, opt2), opt3);
}



void calculate(ll& score, vector<pair<int, int> >& out) {
    
}

int main() {
    srand(time(0));
    read_from_file();
    
    //int high_score = 0; //highscore inicial
    
    string enter;
    cout << "Press enter" << endl;

    vector<pair<int, int>> vertical_pairs;
    find_pairs(vertical_photos, vertical_pairs);

    for(int i = 0; i < vertical_pairs.size(); i++)
    {
        cerr << "Pair: " << vertical_pairs[i].first << " " << vertical_pairs[i].second << endl;
    }
    
    list<Slide> slides;

    int fullscore;

    for(int i = 0; i < vertical_pairs.size(); i++)
    {
        list<Slide>::iterator bestplace = slides.begin();

        auto it = slides.begin();

        while(it != slides.end())
        {
            int parscore = interest(v)
        }
    }



    /*

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
    */
}
