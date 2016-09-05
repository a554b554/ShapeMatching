#ifndef SHAPEMATCHING_H
#define SHAPEMATCHING_H
#include "munkres.h"
#include "shapedescriptor.h"


double matchCost(const vector<double>& des1, const vector<double>& des2);

Matrix<double> constructCostMat(const vector<vector<double>>& des1, const vector<vector<double>>& des2);

double solveMat(const Matrix<double>& mat);

double shapeMatching(vector<mPoint>& font1, vector<mPoint>& font2, bool rotateInv=true, int thetasize=8, int rsize=5);

#endif // SHAPEMATCHING_H
