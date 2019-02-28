#include <cmath>
#include <algorithm>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

#include "inout.h"
using namespace std;

#define INPUT_FILE "d_metropolis.in"
#define OUTPUT_FILE "d_out.txt"

typedef long long ll;


int dist(int ri, int ci, int rf, int cf) {
    return abs(rf-ri) + abs(cf-ci);
}

struct Car {
    int time, r, c;
    Car() {
        time = 0;
        r = 0;
        c = 0;
    }
};

vector<Ride> rides;

bool comp(const Ride& r1, const Ride& r2)
{
    if(r1.s == r2.s)
    {
        if(r1.f == r2.f) return r1.num < r2.num;
        else return r1.f < r2.f;
    }
    return r1.s < r2.s;
}

bool is_bonus(const Car& c, const Ride& r) {
    //cerr << "Temps d'arribada bonus: " << c.time + dist(c.r, c.c, r.ri, r.ci) + dist(r.ri, r.ci, r.rf, r.cf) << endl;
    return (c.time + dist(c.r, c.c, r.ri, r.ci) < r.s);
}

bool is_possible(const Car& c, const Ride& r) {
    //cerr << "Temps d'arribada: " << c.time + dist(c.r, c.c, r.ri, r.ci) + dist(r.ri, r.ci, r.rf, r.cf) << endl;
    return (c.time + dist(c.r, c.c, r.ri, r.ci) + dist(r.ri, r.ci, r.rf, r.cf) < r.f);
}

void calculate(ll& score, vector<vector<int> >& out) {
    vector<Car> cars(F);
    int curr_ride = 0;
    score = 0;
    out = vector<vector<int> >(F);
    while (curr_ride < N) {
        if (rand()%10 == 0) continue;
        int selected_car = -1;
        Ride& curr = rides[curr_ride];
        vector<int> bonus;
        for (int i = 0; i < F; i++) {
            if (is_bonus(cars[i], curr)) {
                bonus.push_back(i);
            }
        }
        int bs = bonus.size();
        if (bs != 0) {
            selected_car = bonus[rand()%bs];
            score += B;
        }
        else {
            for (int i = 0; i < F; i++) {
                if (is_possible(cars[i], curr)) {
                    bonus.push_back(i);
                    bs = bonus.size();
                    if (bs != 0) {
                        selected_car = bonus[rand()%bs];
                    }
                }
            }
        }
        if (selected_car != -1) {
            //cerr << "LA RUTA " << curr.num << " HA ESTAT SELECCIONADA PEL COTXE " << selected_car << endl;
            Car& mycar = cars[selected_car];
            out[selected_car].push_back(curr.num);
            int pickup_time = max(curr.s, mycar.time + dist(mycar.r, mycar.c, curr.ri, curr.ci));
            int final_time = pickup_time + dist(curr.ri, curr.ci, curr.rf, curr.cf);
            mycar.time = final_time;
            mycar.r = curr.rf;
            mycar.c = curr.cf;
            score += (ll)dist(curr.ri, curr.ci, curr.rf, curr.cf);
            //cerr << "COTXE " << selected_car << ":" << endl;
            //cerr << "  Fila " << mycar.r << endl;
            //cerr << "  Columna " << mycar.c << endl;
            //cerr << "  Temps " << mycar.time << endl;
        }
        curr_ride++;
    }
    
}

int main() {
    srand(time(0));
    read_from_file(INPUT_FILE, rides);
    int high_score = 0; //highscore inicial
    sort(rides.begin(), rides.end(), comp);
    string enter;
    cout << "Press enter" << endl;
    ll iter = 0;
    while (iter%100 != 0 or getline(cin, enter)) {
        ll score;
        vector<vector<int> > out;
        calculate(score, out);
        cout << "Finished iteration with " << score << " points" << endl;
        if (score > high_score) {
            cout << "Updating output file..." << endl;
            write_to_file(OUTPUT_FILE, out);
            cout << "Output file updated" << endl;
            high_score = score;
        }
        iter++;
        if (iter%100 == 0) cout << "Press enter" << endl;
    } 
}
