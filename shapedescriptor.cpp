#include "shapedescriptor.h"

ShapeDescriptor::ShapeDescriptor(vector<mPoint> pts):
    shape(pts)
{

}

void ShapeDescriptor::setBinSize(int theta, int r){
    thetasize = theta;
    rsize = r;
    cout<<"theta size: "<<thetasize;
    cout<<" rsize: "<<rsize<<endl;
}

void ShapeDescriptor::computeDes(int id, bool rotateInv){
    double maxdist = getMaxDist(id);
    double mindist = getMinDist(id);
    double maxlogdist = log(maxdist);
    double minlogdist = log(mindist);
    vector<double> bin(thetasize*rsize);
    //the descriptor is arranged as
    //logr0theta0 logr0theta1... logr0thetaN logr1theta0...
    //fill the descriptor
    vector<mPoint> tshape = shape;
    if(rotateInv){
        mPoint p0 = shape[id];
        double dx,dy;
        if(id==shape.size()-1){
            dx = shape[0].x-p0.x;
            dy = shape[0].y-p0.y;
        }
        else{
            dx = shape[id+1].x-p0.x;
            dy = shape[id+1].y-p0.y;
        }
        double l=sqrt(dx*dx+dy*dy);
        double sint = dy/l;
        double cost = dx/l;
        //perform rotation
        for(int i=0; i<tshape.size(); i++){
            tshape[i].rotatefrom(p0,sint,cost);
        }
    }
    fill(bin.begin(), bin.end(), 0);
    for(int i=0; i<tshape.size(); i++){
        if(i==id){
            continue;
        }
        double dist = tshape[i].dist(tshape[id]);
        double logdist = log(dist);
        int logrID = (logdist-minlogdist)/(maxlogdist-minlogdist)*rsize;
        if(logrID==rsize){
            logrID--;
        }
        double dx = tshape[i].x - tshape[id].x;
        double dy = tshape[i].y - tshape[id].y;
        double theta = atan2(dy,dx)+M_PI;
        int thetaID = theta/(2*M_PI)*thetasize;
        if(thetaID==thetasize){
            thetaID--;
        }
        int locID = thetaID+logrID*thetasize;
        bin[locID] = bin[locID]+1;
    }

    //normalize histogram
    double sum = 0;
    for(auto b:bin){
        sum += b;
    }
    for(int i=0; i<bin.size(); i++){
        bin[i] /= sum;
    }
    des.push_back(bin);
}


void ShapeDescriptor::computeDes(bool rotateInv){
    des.clear();
    for(int i=0; i<shape.size(); i++){
//        cout<<"compute descriptor: "<<i<<endl;
        computeDes(i, rotateInv);
    }
}

double ShapeDescriptor::getMaxDist(int id){
    double maxdist=0;
    mPoint p0 = shape[id];
    for(int i=0; i<shape.size(); i++){
        if(i==id){
            continue;
        }
        double td = p0.dist(shape[i]);
        if(td>maxdist){
            maxdist = td;
        }
    }
    return maxdist;
}

double ShapeDescriptor::getMinDist(int id){
    double mindist=INFINITY;
    mPoint p0 = shape[id];
    for(int i=0; i<shape.size(); i++){
        if(i==id){
            continue;
        }
        double td = p0.dist(shape[i]);
        if(td<mindist){
            mindist = td;
        }
    }
    return mindist;
}

void ShapeDescriptor::printDes(int id){
    double sum=0;
    for(int r=0; r<rsize; r++){
        for(int the=0; the<thetasize; the++){
            cout<<des[id][r*thetasize+the]<<" ";
            sum+=des[id][r*thetasize+the];
        }
        cout<<endl;
    }
    cout<<"sum check: "<<sum<<endl;
}






