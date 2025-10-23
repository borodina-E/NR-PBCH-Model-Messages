#ifndef CONVERTTOEIGENMATRIX_H
#define CONVERTTOEIGENMATRIX_H

#include <iostream>
#include <vector>
#include <Eigen/Dense>
using namespace Eigen;
using namespace std;

MatrixXd convertToEigenMatrix(const vector<vector<int>>&);
#endif