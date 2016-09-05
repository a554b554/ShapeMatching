#include "mpoint.h"

mPoint::mPoint()
{

}

mPoint::mPoint(double _x, double _y):x(_x),y(_y){

}



double mPoint::dist(mPoint p){
    return std::sqrt((x-p.x)*(x-p.x)+(y-p.y)*(y-p.y));
}

void loadPlist(vector<vector<mPoint> > &plist, string filename){
    plist.clear();

    std::ifstream infile(filename);
    std::string line;
    while (std::getline(infile, line))
    {
        int size=0;
        vector<mPoint> pts;
        std::istringstream iss(line);
        double x, y;
        int f=0;
        while(iss >> x >> y){
//            cout<<x<<" "<<y<<endl;
//            size++;
            mPoint pt;
            pt.x = x;
            pt.y = y;
            if(f==0){
                pts.push_back(pt);
                f=1;
            }
            else{
                f=0;
            }
        }
//        cout<<size;
//        return;
        plist.push_back(pts);
    }
}

void mPoint::rotatefrom(mPoint p, double sint, double cost){
    double deltx = this->x-p.x;
    double delty = this->y-p.y;
    double _deltx = deltx*cost+delty*sint;
    double _delty = -deltx*sint+delty*cost;
    this->x = p.x+_deltx;
    this->y = p.y+_delty;
}
