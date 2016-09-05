#ifndef SHAPEDESCRIPTOR_H
#define SHAPEDESCRIPTOR_H
#include "mpoint.h"
#include <vector>
#include <cassert>

using namespace std;

class ShapeDescriptor
{
public:
    ShapeDescriptor(vector<mPoint> pts);
    vector<mPoint> shape;
    void setBinSize(int theta, int r);
    vector<double> getDes(int id);
    void printDes(int id);
    void computeDes(int id, bool rotateInv);
    void computeDes(bool rotateInv);
    double getMaxDist(int id);
    double getMinDist(int id);
    vector<vector<double>> des;

private:
    int thetasize;
    int rsize;

    //the descriptor is arranged as
    //logr0theta0 logr0theta1... logr0thetaN logr1theta0...
};




#endif // SHAPEDESCRIPTOR_H
