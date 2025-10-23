#include <iostream>
#include <vector>
#include <Eigen/Dense>
using namespace Eigen;
using namespace std;

RowVectorXd convertToEigenVector(const vector<uint8_t>& vec)
{
	int size = vec.size();
	RowVectorXd eigen_vector(size);

	for(int i = 0; i < size; i++) {
		eigen_vector(i) = static_cast<double>(vec[i]);
	}
	return eigen_vector;
}