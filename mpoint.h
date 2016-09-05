#ifndef MPOINT_H
#define MPOINT_H
#include <cmath>
#include <string>
#include <sstream>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

class mPoint
{
public:
    mPoint();
    mPoint(double _x, double _y);
    double x;
    double y;
    double dist(mPoint p);
    void rotatefrom(mPoint p, double sint, double cost); // (dx, dy) is the initial vector that rotate to x-axis
};

void loadPlist(vector<vector<mPoint>>& plist, string filename);

#endif // MPOINT_H
