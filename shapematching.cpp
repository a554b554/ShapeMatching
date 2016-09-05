#include "shapematching.h"

double matchCost(const vector<double> &des1, const vector<double> &des2){
    double ans=0;
    assert(des1.size()==des2.size());


    for(int i=0; i<des1.size(); i++){
//        cout<<"des1: "<<des1[i]<<" des2: "<<des2[i]<<endl;
        if(des1[i]==0&&des2[i]==0){
            continue;
        }
        ans+=(des1[i]-des2[i])*(des1[i]-des2[i])/(des1[i]+des2[i]);
    }
//    cout<<"cost: "<<ans<<endl;
    return 0.5*ans;
}


Matrix<double> constructCostMat(const vector<vector<double> > &des1, const vector<vector<double> > &des2){
    Matrix<double> costMat(des1.size(), des2.size());
    for(int i=0; i<costMat.rows(); i++){
        for(int j=0; j<costMat.columns(); j++){
            costMat(i,j)=matchCost(des1[i],des2[j]);
        }
    }

    int nrows = costMat.rows();
    int ncols = costMat.columns();
//    for ( int row = 0 ; row < nrows ; row++ ) {
//        for ( int col = 0 ; col < ncols ; col++ ) {
//            std::cout << costMat(row,col) << ",";
//        }
//        std::cout << std::endl;
//    }
//    std::cout << std::endl;
//    cout<<nrows<<" "<<ncols<<endl;
    return costMat;
}


double solveMat(const Matrix<double> &mat){
    Munkres<double> m;
    Matrix<double> d(mat);
    m.solve(d);
    double cost = 0;

    for ( int row = 0 ; row < d.rows() ; row++ ) {
        for ( int col = 0 ; col < d.columns() ; col++ ) {
//            std::cout << d(row,col) << ",";
            if(d(row,col)==0){
                cost += mat(row,col);
            }
        }
//        std::cout << std::endl;
    }
//    std::cout << std::endl;
    return cost;
}

double shapeMatching(vector<mPoint> &font1, vector<mPoint> &font2, bool rotateInv, int thetasize, int rsize){
    cout<<"start matching..."<<endl;
    ShapeDescriptor d0(font1);
    ShapeDescriptor d1(font2);
    d0.setBinSize(thetasize, rsize);
    d1.setBinSize(thetasize, rsize);
    d0.computeDes(rotateInv);
    d1.computeDes(rotateInv);
    Matrix<double> costmat = constructCostMat(d0.des, d1.des);
    return solveMat(costmat);
}


//Munkres<double> m;
//	m.solve(matrix);

//	// Display solved matrix.
//	for ( int row = 0 ; row < nrows ; row++ ) {
//		for ( int col = 0 ; col < ncols ; col++ ) {
//			std::cout.width(2);
//			std::cout << matrix(row,col) << ",";
//		}
//		std::cout << std::endl;
//	}
