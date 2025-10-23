#ifndef POLARDECODING_H
#define POLARDECODING_H

#include <iostream>
#include <cmath>
#include <vector>
#include "PolarCodingInterleaverPattern.h"
#include "PolarSequenceReliability.h"
#include "kron.h"
#include <Eigen/Dense>
#include "convertToEigenVector.h"
#include "convertToEigenMatrix.h"
#include "convertRowVectorToUint8.h"

using namespace Eigen;
using namespace std;

vector<uint8_t> polarDecoding(vector<uint8_t>&);
#endif