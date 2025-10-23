#include <vector>
#include <Eigen/Dense>
using namespace Eigen;
using namespace std;

MatrixXd convertToEigenMatrix(const vector<vector<int>>& vec_matrix)
{
	int rows = vec_matrix.size();
	int cols = vec_matrix[0].size();

	MatrixXd eigen_matrix(rows, cols);

	for(int i = 0; i < rows; i++) {
		for(int j = 0; j < cols; j++) {
			eigen_matrix(i, j) = static_cast<double>(vec_matrix[i][j]);
		}
	}
	return eigen_matrix;
}