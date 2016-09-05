#include "test.h"

void test1(){
    vector<vector<mPoint>> plistsa;
    vector<vector<mPoint>> plistsb;
    loadPlist(plistsa,"./Data/char_a");
    loadPlist(plistsb,"./Data/char_b");
    ShapeDescriptor d0(plistsa[0]);
    ShapeDescriptor d1(plistsb[0]);
    d0.setBinSize(8,5);
    d1.setBinSize(8,5);
    d0.computeDes(false);
    d1.computeDes(false);
    Matrix<double> costmat = constructCostMat(d0.des,d1.des);
    cout<<"cost: "<<solveMat(costmat)<<endl;
}

void testrotatefrom(){
    mPoint g0,g1;
    g0.x=1;
    g0.y=1;
    g1.x=1;
    g1.y=2;
    mPoint g3(4,0);
    double dx = g1.x-g0.x;
    double dy = g1.y-g0.y;
    double l = sqrt(dx*dx+dy*dy);
//    cout<<dy/l<<" "<<dx/l<<endl;
    g3.rotatefrom(g0,dy/l,dx/l);
    cout<<g3.x<<" "<<g3.y<<endl;
}


void testrotationInv(){
    vector<vector<mPoint>> plists;
    loadPlist(plists,"./Data/char_a");
    vector<mPoint> pts = plists[0];
    vector<mPoint> ptsr = plists[1];
    for(int i=0; i<ptsr.size(); i++){
        ptsr[i].rotatefrom(mPoint(0,0),0,-1);
    }
    cout<<shapeMatching(pts,ptsr)<<endl;
}


