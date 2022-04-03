/**
 * Description: Program that uses the Monte Carlo-method to determine Pi.
 * File: MCPi.cpp
 * Version: 1.0
 * Author: Sebastiano Bäcklund <sl222sw@student.lnu.se>
 */

#include <iostream>
#include <random>
#include <iomanip>
#include <cmath>

using namespace std;

const double R = 100, MIN = 0, PI = M_PI;
random_device ran;
mt19937 mt(ran());

struct Coord {
    double x, y;
};

Coord throwArrow();
bool below(Coord point);
void throwSeries(int n);
void runSeries(int total, int start, int incr);

int main() {
    runSeries(10000, 100, 100);
    // total amount of arrow are 10.000, starting at 100 arrow, incrementing with 100 arrow each iteration

    return 0;
}

Coord throwArrow() {
    uniform_real_distribution<double> interval(MIN, R);
    Coord randomPoint{interval(mt), interval(mt)};
    // create instance of struct Coord, with members x and y randomized between MIN and R (0-100)
    // function returns a random point on the "graph"

    return randomPoint;
}

bool below(Coord point) {
    if ((point.x * point.x + point.y * point.y) < (R * R)) return true;
    // if x*x + y*y < R*R then the arrow is below the quarter circle arc
    else return false;
    // if not, then the arrow is located outside of the circle
}

void throwSeries(int n) {
    int arrowsInCircle = 0;

    for (int i = 0; i < n; i++) {
        // throw n amount of arrows, check if each arrow is below the quarter circle arc
        if (below(throwArrow())) arrowsInCircle++;
    }

    double estPi = 4*(double)arrowsInCircle/(double)n;
    // formula for estimating Pi, 4 * arrowsInCircle/arrowsThrown
    double relFel = ((estPi-PI)/PI)*100;
    // formula for calculating the relative fault

    // printing a series of n-arrows
    if (estPi == (int)estPi) {
        // if 'estPi' is an integer, I.E. 3
        cout<<setw(5)<<setfill(' ')<<n<<"   ";
        cout<<left<<setw(6)<<setfill('0')<<estPi<<" ";
        cout<<right<<setw(7)<<setfill(' ')<<setprecision(1)<<fixed<<relFel<<setprecision(5)<<endl;
    } else {
        cout<<setw(5)<<setfill(' ')<<n<<" "<<setw(2)<<" ";
        cout<<left<<setw(7)<<setfill('0')<<estPi<<" ";
        cout<<right<<setw(7)<<setfill(' ')<<setprecision(1)<<fixed<<relFel<<setprecision(5)<<endl;
    }
}

void runSeries(int total, int start, int incr) {
    // function for running multiple series
    cout<<setw(5)<<"n"<<setw(7)<<"pi"<<setw(14)<<"Rel. fault"<<endl;
    cout<<setw(6)<<setfill('-')<<"|"<<setw(10)<<setfill('-')<<"|"<<setw(7)<<setfill('-')<<"-"<<endl;

    for (int i = start; i <= total; i+= incr) {
        throwSeries(i);
    }
}