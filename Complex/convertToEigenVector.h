#ifndef CONVERTTOEIGENVECTOR_H
#define CONVERTTOEIGENVECTOR_H

#include <iostream>
#include <vector>
#include <Eigen/Dense>
using namespace Eigen;
using namespace std;

RowVectorXd convertToEigenVector(const vector<uint8_t>&);
#endif