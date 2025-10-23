#ifndef CONVERTROWVECTORYOUINT8_H
#define CONVERTROWVECTORYOUINT8_H

#include <iostream>
#include <vector>
#include <Eigen/Dense>
using namespace Eigen;
using namespace std;

vector<uint8_t> convertRowVectorToUint8(const RowVectorXd&);
#endif