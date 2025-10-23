#include <iostream>
#include <vector>
#include <Eigen/Dense>
using namespace Eigen;
using namespace std;

vector<uint8_t> convertRowVectorToUint8(const RowVectorXd& eigen_vector)
{
	int size = eigen_vector.size();
	vector<uint8_t> result;
	result.reserve(size);
	for(int i = 0; i < size; i++) {
		result.push_back(static_cast<uint8_t>(round(eigen_vector(i))));
	}
	return result;
}